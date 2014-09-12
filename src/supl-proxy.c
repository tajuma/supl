/*
** SUPL Proxy
**
** Copyright (c) 2007 Tatu Mannisto <tatu a-t tajuma d-o-t com>
** All rights reserved.
** Redistribution and modifications are permitted subject to BSD license.
**
*/

#include <stdio.h>
#include <fcntl.h>
#include <netdb.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

#include "supl.h"
#include "asn-supl/ULP-PDU.h"

#define SUPL_PORT "7275"

/* Make these what you want for cert & key files */
#define CERTF "srv-cert.pem"
#define KEYF  "srv-priv.pem"

static void ssl_error(SSL *ssl, int err) {
  int ssl_err = SSL_get_error(ssl, err);

  fprintf(stderr, "Error: SSL_accept() error code %d\n", ssl_err);
  if (ssl_err == SSL_ERROR_SYSCALL) {
    if (err == -1) fprintf(stderr, "  I/O error (%s)\n", strerror(errno));
    if (err == 0) fprintf(stderr, "  SSL peer closed connection\n");
  }
}

static int ssl_accept(int port, supl_ctx_t *client_ctx) {
  int err;
  int listen_sd;
  int sd;
  struct sockaddr_in sa_serv;
  struct sockaddr_in sa_cli;
  socklen_t client_len;
  SSL_CTX* ctx;
  SSL*     ssl;
  X509*    client_cert;
  char*    str;
  SSL_METHOD *meth;
  
  /* SSL preliminaries. We keep the certificate and key with the context. */

  SSL_load_error_strings();
  SSLeay_add_ssl_algorithms();
  // meth = TLSv1_server_method();
  meth = SSLv23_server_method();
  ctx = SSL_CTX_new (meth);
  if (!ctx) {
    return 0;
  }
  
  if (SSL_CTX_use_certificate_file(ctx, CERTF, SSL_FILETYPE_PEM) <= 0) {
    fprintf(stderr, "Error: Valid server certificate not found in " CERTF "\n");
    return 0;
  }
  if (SSL_CTX_use_PrivateKey_file(ctx, KEYF, SSL_FILETYPE_PEM) <= 0) {
    fprintf(stderr, "Error: Valid server private key not found in " CERTF "\n");
    return 0;
  }

  if (!SSL_CTX_check_private_key(ctx)) {
    fprintf(stderr, "Error: Private key does not match the certificate public key\n");
    return 0;
  }

  /* ----------------------------------------------- */
  /* Prepare TCP socket for receiving connections */

  listen_sd = socket(AF_INET, SOCK_STREAM, 0);
  if (listen_sd == -1) return 0;
  
  memset(&sa_serv, '\0', sizeof(sa_serv));
  sa_serv.sin_family      = AF_INET;
  sa_serv.sin_addr.s_addr = INADDR_ANY;
  sa_serv.sin_port        = htons(port);          /* Server Port number */
  
  err = bind(listen_sd, (struct sockaddr*) &sa_serv, sizeof (sa_serv));
  if (err == -1) {
    fprintf(stderr, "Error: Could not bind to port %d (%s)\n", port, strerror(errno));
    return 0;
  }
	     
  err = listen(listen_sd, 5);
  if (err == -1) {
    fprintf(stderr, "Error: listen() (%s)\n", strerror(errno));
    return 0;
  }

  client_len = sizeof(sa_cli);
  sd = accept(listen_sd, (struct sockaddr*)&sa_cli, &client_len);
  if (sd == -1) {
    fprintf(stderr, "Error: accept() (%s)\n", strerror(errno));
    return 0;
  }
  close(listen_sd);

  {
    char buffer[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &sa_cli.sin_addr.s_addr, buffer, sizeof(buffer));
    fprintf(stderr, "Connection from %s:%d\n", buffer, ntohs(sa_cli.sin_port));
  }
  
  /* ----------------------------------------------- */
  /* TCP connection is ready. Do server side SSL. */

  ssl = SSL_new(ctx);
  SSL_set_fd(ssl, sd);
  err = SSL_accept(ssl);
  if (err != 1) {
    ssl_error(ssl, err);
    return 0;
  }

  printf ("SSL connection using %s\n", SSL_get_cipher (ssl));
  
  /* Get client's certificate */

  client_cert = SSL_get_peer_certificate (ssl);
  if (client_cert != NULL) {
    printf ("Client certificate:\n");
    
    str = X509_NAME_oneline (X509_get_subject_name (client_cert), 0, 0);
    if (!str) return 0;
    printf ("\t subject: %s\n", str);
    OPENSSL_free (str);
    
    str = X509_NAME_oneline (X509_get_issuer_name  (client_cert), 0, 0);
    if (!str) return 0;
    printf ("\t issuer: %s\n", str);
    OPENSSL_free (str);
    
    /* We could do all sorts of certificate verification stuff here before
       deallocating the certificate. */
    
    X509_free (client_cert);
  } else {
    printf ("Client does not have certificate.\n");
  }

  client_ctx->ssl = ssl;
  client_ctx->ssl_ctx = ctx;

  return 1;
}

int main(int argc, char *argv[])
{
  supl_ctx_t server_ctx;
  supl_ctx_t client_ctx;

  if (argc != 2) {
    fprintf(stderr, "Usage: %s supl-server\n", argv[0]);
    exit(1);
  }

  supl_set_debug(stderr, SUPL_DEBUG_DEBUG | SUPL_DEBUG_SUPL);

  supl_ctx_new(&server_ctx);
  supl_ctx_new(&client_ctx);

  /* get a client */

  if (!ssl_accept(7275, &client_ctx)) {
    return 42;
  }

  /* connect to the server */

  if (supl_server_connect(&server_ctx, argv[1]) < 0) {
    fprintf(stderr, "Error: Could not connect to server\n");
    return E_SUPL_CONNECT;
  }

  /* DATA EXCHANGE - Receive message and send reply. */

  while (1) {
    supl_ulp_t pdu;
    PDU_t *rrlp;

    /* read from mobile */

    if (supl_ulp_recv(&client_ctx, &pdu) < 0) {
      return -42;
    }
    
    fprintf(stdout, "mobile => server\n");
    xer_fprint(stdout, &asn_DEF_ULP_PDU, pdu.pdu);
    fprintf(stdout, "\n");
    
    /* write to server */
    
    (void)supl_ulp_send(&server_ctx, &pdu);

    if (pdu.pdu->message.present == UlpMessage_PR_msSUPLEND) 
      break;

    supl_ulp_free(&pdu);

    /* get answer from server */

    if (supl_ulp_recv(&server_ctx, &pdu) < 0) {
      return -44;
    }

    fprintf(stdout, "server => mobile\n");
    xer_fprint(stdout, &asn_DEF_ULP_PDU, pdu.pdu);
    fprintf(stdout, "\n");

    if (pdu.pdu->message.present == UlpMessage_PR_msSUPLPOS) {
      if (supl_decode_rrlp(&pdu, &rrlp) < 0) {
	supl_ulp_free(&pdu);
	return E_SUPL_DECODE_RRLP;
      }

      fprintf(stdout, "=== Embedded RRLP message ===\n");
      xer_fprint(stdout, &asn_DEF_PDU, rrlp);
      fprintf(stdout, "\n");
    }

    /* and hand over to client */
    (void)supl_ulp_send(&client_ctx, &pdu);

    supl_ulp_free(&pdu);
  }

  supl_close(&server_ctx);
  supl_close(&client_ctx);

  supl_ctx_free(&server_ctx);
  supl_ctx_free(&client_ctx);

  return 0;
}

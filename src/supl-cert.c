/* crude hack to get ca and server keys and certificates done */
/* based on example code from OpenSSL */

#include <stdio.h>
#include <stdlib.h>

#include <openssl/pem.h>
#include <openssl/conf.h>
#include <openssl/x509v3.h>

static char *domain;

static int mkit_ca(X509 **x509p, EVP_PKEY **pkeyp, int bits, int serial, int days);
static int mkit_srv(X509 **x509p, EVP_PKEY **pkeyp, EVP_PKEY *sign_key, X509 *sign_cert, int bits, int serial, int days);

int main(int argc, char *argv[])
	{
	BIO *bio_err;
	X509 *x509=0;
	X509 *sign_cert=0;
	EVP_PKEY *pkey=0;
	EVP_PKEY *sign_key=0;

	if (argc != 2) {
	  fprintf(stderr, "usage: %s domain-name\n", argv[0]);
	  exit(1);
	}
	domain = argv[1];

	CRYPTO_mem_ctrl(CRYPTO_MEM_CHECK_ON);

	bio_err=BIO_new_fp(stderr, BIO_NOCLOSE);

	mkit_ca(&x509,&pkey,1024,42,365);

#if 0
	RSA_print_fp(stdout,pkey->pkey.rsa,0);
	X509_print_fp(stdout,x509);
#endif

	{
	  FILE *f;
	  f = fopen("ca-priv.pem", "w");
	  PEM_write_PrivateKey(f,pkey,NULL,NULL,0,NULL, NULL);
	  fclose(f);
	}
	{
	  FILE *f;
	  f = fopen("ca-cert.pem", "w");
	  PEM_write_X509(f, x509);
	  fclose(f);
	}

	{
	  FILE *f;
	  f = fopen("ca-priv.pem", "r");
	  if (!f) {
	    fprintf(stderr, "Can not open signature key file ca-priv.pem\n");
	    exit(1);
	  }
	  sign_key = PEM_read_PrivateKey(f, 0, 0, 0);
	  fclose(f);
	  if (!sign_key) {
	    fprintf(stderr, "Signature key not good\n");
	    exit(1);
	  }
	}

	{
	  FILE *f;
	  f = fopen("ca-cert.pem", "r");
	  if (!f) {
	    fprintf(stderr, "Can not open CA certificate file ca-priv.pem\n");
	    exit(1);
	  }
	  sign_cert = PEM_read_X509(f, 0, 0, 0);
	  fclose(f);
	  if (!sign_cert) {
	    fprintf(stderr, "CA cert not good\n");
	    exit(1);
	  }
	}

	X509_free(x509);
	EVP_PKEY_free(pkey);

	x509 = 0;
	pkey = 0;

	mkit_srv(&x509,&pkey,sign_key,sign_cert,1024,0xbeef,365);

#if 0
	RSA_print_fp(stdout,pkey->pkey.rsa,0);
	X509_print_fp(stdout,x509);
#endif

	{
	  FILE *f;
	  f = fopen("srv-priv.pem", "w");
	  PEM_write_PrivateKey(f,pkey,NULL,NULL,0,NULL, NULL);
	  fclose(f);
	}
	{
	  FILE *f;
	  f = fopen("srv-cert.pem", "w");
	  PEM_write_X509(f, x509);
	  fclose(f);
	}

	X509_free(x509);
	EVP_PKEY_free(pkey);

	/* Only needed if we add objects or custom extensions */
	X509V3_EXT_cleanup();
	OBJ_cleanup();

	CRYPTO_mem_leaks(bio_err);
	BIO_free(bio_err);
	return(0);
	}

static void callback(p, n, arg)
int p;
int n;
void *arg;
	{
	return;
	}

static int mkit_ca(x509p,pkeyp,bits,serial,days)
X509 **x509p;
EVP_PKEY **pkeyp;
int bits;
int serial;
int days;
	{
	X509 *x;
	EVP_PKEY *pk;
	RSA *rsa;
	X509_NAME *name=NULL;
	X509_EXTENSION *ex=NULL;

	
	if ((pkeyp == NULL) || (*pkeyp == NULL))
		{
		if ((pk=EVP_PKEY_new()) == NULL)
			{
			abort(); 
			return(0);
			}
		}
	else
		pk= *pkeyp;

	if ((x509p == NULL) || (*x509p == NULL))
		{
		if ((x=X509_new()) == NULL)
			goto err;
		}
	else
		x= *x509p;

	rsa=RSA_generate_key(bits,RSA_F4,callback,NULL);
	if (!EVP_PKEY_assign_RSA(pk,rsa))
		{
		abort();
		goto err;
		}
	rsa=NULL;

	X509_set_version(x,2);
	ASN1_INTEGER_set(X509_get_serialNumber(x),serial);
	X509_gmtime_adj(X509_get_notBefore(x),(long)-60*60*24*31);
	X509_gmtime_adj(X509_get_notAfter(x),(long)60*60*24*days);
	X509_set_pubkey(x,pk);

	name=X509_get_subject_name(x);

	/* This function creates and adds the entry, working out the
	 * correct string type and performing checks on its length.
	 * Normally we'd check the return value for errors...
	 */
	X509_NAME_add_entry_by_txt(name,"C",
				   MBSTRING_ASC, (const unsigned char *)"FI", -1, -1, 0);
	X509_NAME_add_entry_by_txt(name,"O",
				   MBSTRING_ASC, (const unsigned char *)"SuperDupper CA", -1, -1, 0);
	X509_NAME_add_entry_by_txt(name,"CN",
				   MBSTRING_ASC, (const unsigned char *)domain, -1, -1, 0);

	X509_set_issuer_name(x,name);

	/* Add extension using V3 code: we can set the config file as NULL
	 * because we wont reference any other sections. We can also set
         * the context to NULL because none of these extensions below will need
	 * to access it.
	 */

	ex = X509V3_EXT_conf_nid(NULL, NULL, NID_netscape_ssl_server_name, domain);
	X509_add_ext(x,ex,-1);
	X509_EXTENSION_free(ex);

	ex = X509V3_EXT_conf_nid(NULL, NULL, NID_netscape_cert_type,
				 "sslCA");
	X509_add_ext(x,ex,-1);
	X509_EXTENSION_free(ex);

	ex = X509V3_EXT_conf_nid(NULL, NULL, NID_basic_constraints,
				 "critical,CA:TRUE");
	X509_add_ext(x,ex,-1);
	X509_EXTENSION_free(ex);

	ex = X509V3_EXT_conf_nid(NULL, NULL, NID_key_usage, 
				 "critical,keyCertSign,cRLSign");
	X509_add_ext(x,ex,-1);
	X509_EXTENSION_free(ex);

	if (!X509_sign(x,pk,EVP_sha1()))
		goto err;

	*x509p=x;
	*pkeyp=pk;
	return(1);
err:
	return(0);
	}

static int mkit_srv(x509p,pkeyp,sign_key,sign_cert,bits,serial,days)
X509 **x509p;
EVP_PKEY **pkeyp;
EVP_PKEY *sign_key;
X509 *sign_cert;
int bits;
int serial;
int days;
	{
	X509 *x;
	EVP_PKEY *pk;
	RSA *rsa;
	X509_NAME *name=NULL;
	X509_EXTENSION *ex=NULL;

	
	if ((pkeyp == NULL) || (*pkeyp == NULL))
		{
		if ((pk=EVP_PKEY_new()) == NULL)
			{
			abort(); 
			return(0);
			}
		}
	else
		pk= *pkeyp;

	if ((x509p == NULL) || (*x509p == NULL))
		{
		if ((x=X509_new()) == NULL)
			goto err;
		}
	else
		x= *x509p;

	rsa=RSA_generate_key(bits,RSA_F4,callback,NULL);
	if (!EVP_PKEY_assign_RSA(pk,rsa))
		{
		abort();
		goto err;
		}
	rsa=NULL;

	X509_set_version(x,2);
	ASN1_INTEGER_set(X509_get_serialNumber(x),serial);
	X509_gmtime_adj(X509_get_notBefore(x),(long)-60*60*24*31);
	X509_gmtime_adj(X509_get_notAfter(x),(long)60*60*24*days);
	X509_set_pubkey(x,pk);

	name=X509_get_subject_name(x);

	/* This function creates and adds the entry, working out the
	 * correct string type and performing checks on its length.
	 * Normally we'd check the return value for errors...
	 */
	X509_NAME_add_entry_by_txt(name,"C",
				   MBSTRING_ASC, (const unsigned char *) "FI", -1, -1, 0);
	X509_NAME_add_entry_by_txt(name,"CN",
				   MBSTRING_ASC, (const unsigned char *)domain, -1, -1, 0);

	name = X509_get_subject_name(sign_cert);
	X509_set_issuer_name(x,name);

	/* Add extension using V3 code: we can set the config file as NULL
	 * because we wont reference any other sections. We can also set
         * the context to NULL because none of these extensions below will need
	 * to access it.
	 */

	ex = X509V3_EXT_conf_nid(NULL, NULL, NID_key_usage, 
				 "critical,keyEncipherment,dataEncipherment,keyAgreement,nonRepudiation");
	X509_add_ext(x,ex,-1);
	X509_EXTENSION_free(ex);

	if (!X509_sign(x,sign_key,EVP_sha1()))
		goto err;

	*x509p=x;
	*pkeyp=pk;
	return(1);
err:
	return(0);
	}

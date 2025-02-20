/*
** SUPL clinet cli code
**
** Copyright (c) 2007 Tatu Mannisto <tatu a-t tajuma d-o-t com>
** All rights reserved.
** Redistribution and modifications are permitted subject to BSD license.
**
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <getopt.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>

#include "supl.h"

typedef enum { FORMAT_DEFAULT, FORMAT_HUMAN } format_t;

static struct fake_pos_s {
  int valid;
  double lat, lon;
  int uncertainty;
} fake_pos = {
  0, 0.0, 0.0, 0
};

static time_t utc_time(int week, long tow) {
  time_t t;

  /* Jan 5/6 midnight 1980 - beginning of GPS time as Unix time */
  t = 315964801;

  /* soon week will wrap again, uh oh... */
  /* TS 44.031: GPSTOW, range 0-604799.92, resolution 0.08 sec, 23-bit presentation */
  t += (1024 + week) * 604800 + tow*0.08;

  return t;
} 

static int supl_consume_1(supl_assist_t *ctx) {
  if (ctx->set & SUPL_RRLP_ASSIST_REFLOC) {
    fprintf(stdout, "Reference Location:\n");
    fprintf(stdout, "  Lat: %f\n", ctx->pos.lat);
    fprintf(stdout, "  Lon: %f\n", ctx->pos.lon);
    fprintf(stdout, "  Uncertainty: %d (%.1f m)\n", 
	    ctx->pos.uncertainty, 10.0*(pow(1.1, ctx->pos.uncertainty)-1));
  }

  if (ctx->set & SUPL_RRLP_ASSIST_REFTIME) {
    time_t t;

    t = utc_time(ctx->time.gps_week, ctx->time.gps_tow);

    fprintf(stdout, "Reference Time:\n");
    fprintf(stdout, "  GPS Week: %ld\n", ctx->time.gps_week);
    fprintf(stdout, "  GPS TOW:  %ld %lf\n", ctx->time.gps_tow, ctx->time.gps_tow*0.08);
    fprintf(stdout, "  ~ UTC:    %s", ctime(&t));
  }

  if (ctx->set & SUPL_RRLP_ASSIST_IONO) {
    fprintf(stdout, "Ionospheric Model:\n");
    fprintf(stdout, "  # a0 a1 a2 b0 b1 b2 b3\n");
    fprintf(stdout, "  %g, %g, %g",
	    ctx->iono.a0 * pow(2.0, -30), 
	    ctx->iono.a1 * pow(2.0, -27),
	    ctx->iono.a2 * pow(2.0, -24));
    fprintf(stdout, " %g, %g, %g, %g\n",
	    ctx->iono.b0 * pow(2.0, 11), 
	    ctx->iono.b1 * pow(2.0, 14),
	    ctx->iono.b2 * pow(2.0, 16), 
	    ctx->iono.b3 * pow(2.0, 16));
  }

  if (ctx->set & SUPL_RRLP_ASSIST_UTC) {
    fprintf(stdout, "UTC Model:\n");
    fprintf(stdout, "  # a0, a1 delta_tls tot dn\n");
    fprintf(stdout, "  %g %g %d %d %d %d %d %d\n",
	    ctx->utc.a0 * pow(2.0, -30),
	    ctx->utc.a1 * pow(2.0, -50),
	    ctx->utc.delta_tls,
	    ctx->utc.tot, ctx->utc.wnt, ctx->utc.wnlsf,
	    ctx->utc.dn, ctx->utc.delta_tlsf);
  }

  if (ctx->cnt_eph) {
    int i;

    fprintf(stdout, "Ephemeris:");
    fprintf(stdout, " %d satellites\n", ctx->cnt_eph);
    fprintf(stdout, "  # prn delta_n M0 A_sqrt OMEGA_0 i0 w OMEGA_dot i_dot Cuc Cus Crc Crs Cic Cis");
    fprintf(stdout, " toe IODC toc AF0 AF1 AF2 bits ura health tgd OADA\n");

    for (i = 0; i < ctx->cnt_eph; i++) {
      struct supl_ephemeris_s *e = &ctx->eph[i];

      fprintf(stdout, "  %d %g %g %g %g %g %g %g %g",
	      e->prn, 
	      e->delta_n * pow(2.0, -43), 
	      e->M0 * pow(2.0, -31), 
	      e->A_sqrt * pow(2.0, -19), 
	      e->OMEGA_0 * pow(2.0, -31), 
	      e->i0 * pow(2.0, -31), 
	      e->w * pow(2.0, -31), 
	      e->OMEGA_dot * pow(2.0, -43), 
	      e->i_dot * pow(2.0, -43));
      fprintf(stdout, " %g %g %g %g %g %g",
	      e->Cuc * pow(2.0, -29), 
	      e->Cus * pow(2.0, -29), 
	      e->Crc * pow(2.0, -5), 
	      e->Crs * pow(2.0, -5), 
	      e->Cic * pow(2.0, -29), 
	      e->Cis * pow(2.0, -29));
      fprintf(stdout, " %g %u %g %g %g %g",
	      e->toe * pow(2.0, 4), 
	      e->IODC, 
	      e->toc * pow(2.0, 4), 
	      e->AF0 * pow(2.0, -31), 
	      e->AF1 * pow(2.0, -43), 
	      e->AF2 * pow(2.0, -55));
      fprintf(stdout, " %d %d %d %d %d\n",
	      e->bits,
	      e->ura,
	      e->health,
	      e->tgd,
	      e->AODA * 900);
    }
  }

  if (ctx->cnt_alm) {
    int i;

    fprintf(stdout, "Almanac:");
    fprintf(stdout, " %d satellites\n", ctx->cnt_alm);
    fprintf(stdout, "  # prn e toa Ksii OMEGA_dot A_sqrt OMEGA_0 w M0 AF0 AF1\n");

    for (i = 0; i < ctx->cnt_alm; i++) {
      struct supl_almanac_s *a = &ctx->alm[i];

      fprintf(stdout, "  %d %g %g %g %g ",
	      a->prn, 
	      a->e * pow(2.0, -21), 
	      a->toa * pow(2.0, 12),
	      a->Ksii * pow(2.0, -19),
	      a->OMEGA_dot * pow(2.0, -38));
      fprintf(stdout, "%g %g %g %g %g %g\n",
	      a->A_sqrt * pow(2.0, -11), 
	      a->OMEGA_0 * pow(2.0, -23),
	      a->w * pow(2.0, -23),
	      a->M0 * pow(2.0, -23),
	      a->AF0 * pow(2.0, -20),
	      a->AF1 * pow(2.0, -38));
    }
  }

  return 1;
}

static int supl_consume_2(supl_assist_t *ctx) {
  if (ctx->set & SUPL_RRLP_ASSIST_REFTIME) {
    fprintf(stdout, "T %ld %ld %ld %ld\n", ctx->time.gps_week, ctx->time.gps_tow, 
	    ctx->time.stamp.tv_sec, ctx->time.stamp.tv_usec);
  }

  if (ctx->set & SUPL_RRLP_ASSIST_UTC) {
    fprintf(stdout, "U %d %d %d %d %d %d %d %d\n",
	    ctx->utc.a0, ctx->utc.a1, ctx->utc.delta_tls,
	    ctx->utc.tot, ctx->utc.wnt, ctx->utc.wnlsf,
	    ctx->utc.dn, ctx->utc.delta_tlsf);
  }

  if (ctx->set & SUPL_RRLP_ASSIST_REFLOC) {
    fprintf(stdout, "L %f %f %d\n", ctx->pos.lat, ctx->pos.lon, ctx->pos.uncertainty);
  } else if (fake_pos.valid) {
    fprintf(stdout, "L %f %f %d\n", fake_pos.lat, fake_pos.lon, fake_pos.uncertainty);
  }    

  if (ctx->set & SUPL_RRLP_ASSIST_IONO) {
    fprintf(stdout, "I %d %d %d %d %d %d %d\n",
	    ctx->iono.a0, ctx->iono.a1, ctx->iono.a2,
	    ctx->iono.b0, ctx->iono.b1, ctx->iono.b2, ctx->iono.b3);
  }

  if (ctx->cnt_eph) {
    int i;

    fprintf(stdout, "E %d\n", ctx->cnt_eph);

    for (i = 0; i < ctx->cnt_eph; i++) {
      struct supl_ephemeris_s *e = &ctx->eph[i];

      fprintf(stdout, "e %d %d %d %d %d %d %d %d %d %d",
	      e->prn, e->delta_n, e->M0, e->A_sqrt, e->OMEGA_0, e->i0, e->w, e->OMEGA_dot, e->i_dot, e->e);
      fprintf(stdout, " %d %d %d %d %d %d",
	      e->Cuc, e->Cus, e->Crc, e->Crs, e->Cic, e->Cis);
      fprintf(stdout, " %d %d %d %d %d %d",
	      e->toe, e->IODC, e->toc, e->AF0, e->AF1, e->AF2);
      fprintf(stdout, " %d %d %d %d %d\n",
	      e->bits, e->ura, e->health, e->tgd, e->AODA);
    }
  }

  if (ctx->cnt_alm) {
    int i;

    fprintf(stdout, "A %d\n", ctx->cnt_alm);
    for (i = 0; i < ctx->cnt_alm; i++) {
      struct supl_almanac_s *a = &ctx->alm[i];

      fprintf(stdout, "a %d %d %d %d %d ",
	      a->prn, a->e, a->toa, a->Ksii, a->OMEGA_dot);
      fprintf(stdout, "%d %d %d %d %d %d\n",
	      a->A_sqrt, a->OMEGA_0, a->w, a->M0, a->AF0, a->AF1);
    }
  }

  if (ctx->cnt_acq) {
    int i;

    fprintf(stdout, "Q %d %d\n", ctx->cnt_acq, ctx->acq_time);
    for (i = 0; i < ctx->cnt_acq; i++) {
      struct supl_acquis_s *q = &ctx->acq[i];

      fprintf(stdout, "q %d %d %d ",
	      q->prn, q->parts, q->doppler0);
      if (q->parts & SUPL_ACQUIS_DOPPLER) {
	fprintf(stdout, "%d %d ", q->doppler1, q->d_win); 
      } else {
	fprintf(stdout, "0 0 ");
      }
      fprintf(stdout, "%d %d %d %d ",
	      q->code_ph, q->code_ph_int, q->bit_num, q->code_ph_win);
      if (q->parts & SUPL_ACQUIS_ANGLE) {
	fprintf(stdout, "%d %d\n", q->az, q->el);
      } else {
	fprintf(stdout, "0 0\n");
      }
    }
  }

  return 1;
}

static char *usage_str =
"Usage:\n"
"%s options [supl-server]\n"
"Options:\n"
"  --almanac|-a					request also almanac data\n"
"  --cell gsm:mcc,mns:lac,ci|wcdma:mcc,msn,uc	set current gsm/wcdma cell id\n"
"  --cell gsm:mcc,mns:lac,ci:lat,lon,uncert	set known gsm cell id with position\n"
"  --format|-f human				machine parseable output\n"
"  --debug|-d <n>				1 == RRLP, 2 == SUPL, 4 == DEBUG\n"
"  --debug-file file				write debug to file\n"
"  --port|-p port				remote server port number (7275 by default)\n"
"  --help|-h					show this help\n"
"Example:\n"
"%1$s --cell=gsm:244,5:0x59e2,0x31b0:60.169995,24.939995,127 --cell=gsm:244,5:0x59e2,0x31b0\n"
;

static void usage(char *progname) {
  printf(usage_str, progname);
}

static struct option long_opts[] = {
  { "cell", 1, 0, 0 },
  { "debug", 1, 0, 'd' },
  { "format", 1, 0, 'f' },
  { "test", 1, 0, 't' },
  { "set-pos", 1, 0, 0 },
  { "pos-helper", 1, 0, 0 },
  { "debug-file", 1, 0, 0 },
  { "help", 0, 0, 'h' },
  { "almanac", 0, 0, 'a' },
  { "port", 1, 0, 'p' },
  { 0, 0, 0 }
};

static int parse_fake_pos(char *str, struct fake_pos_s *fake_pos) {
  if (sscanf(str, "%lf,%lf,%d",
	     &fake_pos->lat, &fake_pos->lon, &fake_pos->uncertainty) == 3) {
    fake_pos->valid = 1;
    return 0;
  } 
	
  if (sscanf(str, "%lf,%lf",
	     &fake_pos->lat, &fake_pos->lon) == 2) {
    fake_pos->uncertainty = 121; /* 1000 km */
    fake_pos->valid = 1;
    return 0;
  }

  return 1;
}

int main(int argc, char *argv[]) {
  int err;
  format_t format = FORMAT_DEFAULT;
  int debug_flags = 0;
  FILE *debug_f = 0;
  int request = 0;
  supl_assist_t assist;
  char *server;
  unsigned int port = SUPL_PORT;
  supl_ctx_t ctx;

  supl_ctx_new(&ctx);
  server = "supl.google.com";

  while (1) {
    int opt_index;
    int c;

    c = getopt_long(argc, argv, "ad:f:t:p:", long_opts, &opt_index);
    if (c == -1) break;
    switch (c) {
    case 0:
      switch (opt_index) {

      case 0: /* gsm/wcdma cell */
	{	
	  int mcc, mns, lac, ci, uc, uncertainty;
	  double lat, lon;

	  if (sscanf(optarg, "gsm:%d,%d:%x,%x:%lf,%lf,%d",
		     &mcc, &mns, &lac, &ci, &lat, &lon, &uncertainty) == 7) {
	    supl_set_gsm_cell_known(&ctx, mcc, mns, lac, ci, lat, lon, uncertainty);
	    break;
	  }

	  if (sscanf(optarg, "gsm:%d,%d:%x,%x",
		     &mcc, &mns, &lac, &ci) == 4) {
	    supl_set_gsm_cell(&ctx, mcc, mns, lac, ci);
	    break;
	  }

	  if (sscanf(optarg, "wcdma:%d,%d,%x",
		     &mcc, &mns, &uc) == 3) {
	    supl_set_wcdma_cell(&ctx, mcc, mns, uc);
	    break;
	  }
        }
	
	fprintf(stderr, "Ugh, cell\n");
	break;

      case 4: /* set-pos */
	if (parse_fake_pos(optarg, &fake_pos)) {
	  fprintf(stderr, "Ugh, set-pos\n");
	}
	break;

      case 5: /* pos-helper */

	break;

      case 6: /* debug-file */
	debug_f = fopen(optarg, "w");
	if (!debug_f) {
	  fprintf(stderr, "Error: open debug file %s (%s)\n", optarg, strerror(errno));
	}
	break;

      }

      break;

    case 'a':
      request |= SUPL_REQUEST_ALMANAC;
      break;

    case 'f':
      if (strcmp(optarg, "human") == 0) {
	format = FORMAT_HUMAN;
      }
      break;

    case 'd': 
      {
	int debug = atoi(optarg);

	if (debug & 0x01)
	  debug_flags |= SUPL_DEBUG_RRLP;
	if (debug & 0x02)
	  debug_flags |= SUPL_DEBUG_SUPL;
	if (debug & 0x04)
	  debug_flags |= SUPL_DEBUG_DEBUG;
      }
      break;

    case 't':
      switch (atoi(optarg)) {
      case 0:
	supl_set_gsm_cell(&ctx, 244, 5, 0x59e2, 0x31b0);
	break;
      case 1:
	supl_set_gsm_cell_known(&ctx, 244, 5, 995763, 0, 60.169995, 24.939995, 121);
	break;
      case 2:
	supl_set_gsm_cell(&ctx, 244, 5, 995763, 0x31b0);
	supl_set_gsm_cell_known(&ctx, 244, 5, 995763, 0x31b0, 60.169995, 24.939995, 121);
	break;
      case 3:
	supl_set_wcdma_cell(&ctx, 244, 5, 995763);
	break;
      }
      break;    

    case 'h':
      usage(argv[0]);
      exit(1);

    case 'p':
      port = atoi(optarg);
      if (port == 0 || port > 65535) {
        fprintf(stderr, "Ugh, invalid port\n");
        exit(1);
      }
      break;

    default:
      usage(argv[0]);
      exit(1);
    }
  }

  if (optind + 1 == argc) {
    server = argv[optind];
  }

  if (!fake_pos.valid && getenv("SUPL_FAKE_POS")) {
    parse_fake_pos(getenv("SUPL_FAKE_POS"), &fake_pos);
  }

#ifdef SUPL_DEBUG
  if (debug_flags) {
    supl_set_debug(debug_f ? debug_f : stderr, debug_flags);
  }
#endif

  supl_request(&ctx, request);

  err = supl_get_assist(&ctx, server, port, &assist);
  if (err < 0) {
    fprintf(stderr, "SUPL protocol error %d\n", err);
    exit(1);
  }

  if (debug_f) {
    fclose(debug_f);
  }

  switch (format) {
  case FORMAT_DEFAULT: 
    supl_consume_2(&assist);
    break;
  case FORMAT_HUMAN:
    supl_consume_1(&assist);
    break;
  }

  supl_ctx_free(&ctx);

  return 0;
}

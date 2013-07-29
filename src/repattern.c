/*
 *  RE Pattern Library
 *  Copyright (C) 2013 Intelligently Designed Software Solutions, LLC
 *
 *  @BINDLE_BINARIES_BSD_LICENSE_START@
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are
 *  met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of Bindle Binaries nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 *  IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 *  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 *  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL BINDLE BINARIES BE LIABLE FOR
 *  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 *  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 *  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 *  OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 *  SUCH DAMAGE.
 *
 *  @BINDLE_BINARIES_BSD_LICENSE_END@
 */

///////////////
//           //
//  Headers  //
//           //
///////////////

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <repattern.h>
#include <regex.h>


///////////////////
//               //
//  Definitions  //
//               //
///////////////////

#ifndef PACKAGE_BUGREPORT
#define PACKAGE_BUGREPORT "syzdek@bindlebinaries.com"
#endif
#ifndef PACKAGE_COPYRIGHT
#define PACKAGE_COPYRIGHT ""
#endif
#ifndef PACKAGE_NAME
#define PACKAGE_NAME ""
#endif
#ifndef PACKAGE_VERSION
#define PACKAGE_VERSION ""
#endif

#define REPATTERN_CMD_PRINT     2
#define REPATTERN_CMD_CONTAINS  3
#define REPATTERN_CMD_IS        5
#define REPATTERN_CMD_LIST_SUB  6

#define REPATTERN_MAX_MATCHES    50


//////////////////
//              //
//  Prototypes  //
//              //
//////////////////

int main(int argc, char * argv[]);
const char * prog_name(const char * name);
void repattern_usage(const char * name);
void repattern_verbose(int verbose, int reid, const char * str, size_t nmatch,
   regmatch_t * matches);
void repattern_version(const char * name);


/////////////////
//             //
//  Functions  //
//             //
/////////////////

int main(int argc, char * argv[])
{
   int           cmd;
   int           reid;
   int           re_flags;
   int           c;
   int           long_optindex;
   int           err;
   int           quiet;
   int           verbose;
   ssize_t       sub_index;
   size_t        nmatch;
   regmatch_t    matches[REPATTERN_MAX_MATCHES];
   char          str[1024];
   size_t        len;
   size_t        labels_len;
   const char ** labels;

   // getopt options
   static char   short_opt[] = "cdhIiLqps:vV";
   static struct option long_opt[] =
   {
      // standard options
      {"help",          no_argument, 0, 'h'},
      {"quiet",         no_argument, 0, 'q'},
      {"silent",        no_argument, 0, 'q'},
      {"verbose",       no_argument, 0, 'v'},
      {"version",       no_argument, 0, 'V'},
      // actions
      {"contains",      no_argument, 0, 'c'},
      {"is",            no_argument, 0, 'i'},
      {"list",          no_argument, 0, 'l'},
      {"print",         no_argument, 0, 'p'},
      // regular expressions
      {"email-address", no_argument, 0, REPATTERN_RE_EMAIL_ADDRESS},
      {"host",          no_argument, 0, REPATTERN_RE_HOST},
      {"hostname",      no_argument, 0, REPATTERN_RE_HOSTNAME},
      {"ip-address",    no_argument, 0, REPATTERN_RE_IP_ADDRESS},
      {"ip-port",       no_argument, 0, REPATTERN_RE_IP_PORT},
      {"ipv4-address",  no_argument, 0, REPATTERN_RE_IPV4_ADDRESS},
      {"ipv4-port",     no_argument, 0, REPATTERN_RE_IPV4_PORT},
      {"ipv6-address",  no_argument, 0, REPATTERN_RE_IPV6_ADDRESS},
      {"ipv6-port",     no_argument, 0, REPATTERN_RE_IPV6_PORT},
      {NULL, 0, 0, 0  }
   };

   quiet     = 0;
   verbose   = 0;
   re_flags  = 0;
   cmd       = 0;
   reid      = 0;
   sub_index = -1;

   // processes command line arguments
   optreset = 1;
   while((c = getopt_long(argc, argv, short_opt, long_opt, &long_optindex)) != -1)
   {
      switch(c)
      {
         case -1:       /* no more arguments */
         case 0:        /* long options toggles */
         break;

         case ':':
         case '?':
         fprintf(stderr, "Try `%s --help' for more information.\n", prog_name(argv[0]));
         return(-2);

         case 'c':
         if ((cmd))
         {
            fprintf(stderr, "%s: argument conflicts with exiting command -- -c\n", prog_name(argv[0]));
            fprintf(stderr, "Try `%s --help' for more information.\n", prog_name(argv[0]));
            return(1);
         };
         cmd = REPATTERN_CMD_CONTAINS;
         break;

         case 'h':
         repattern_usage(prog_name(argv[0]));
         return(0);

         case 'I':
         re_flags |= REG_ICASE;
         break;

         case 'i':
         if ((cmd))
         {
            fprintf(stderr, "%s: argument conflicts with exiting command -- -i\n", prog_name(argv[0]));
            fprintf(stderr, "Try `%s --help' for more information.\n", prog_name(argv[0]));
            return(1);
         };
         cmd = REPATTERN_CMD_IS;
         break;

         case 'l':
         if ((cmd))
         {
            fprintf(stderr, "%s: argument conflicts with exiting command -- -l\n", prog_name(argv[0]));
            fprintf(stderr, "Try `%s --help' for more information.\n", prog_name(argv[0]));
            return(1);
         };
         cmd = REPATTERN_CMD_LIST_SUB;
         break;

         case 's':
         sub_index = strtol(optarg, NULL, 0);
         break;

         case 'L':
         re_flags |= REG_NEWLINE;
         break;

         case 'p':
         if ((cmd))
         {
            fprintf(stderr, "%s: argument conflicts with exiting command -- -p\n", prog_name(argv[0]));
            fprintf(stderr, "Try `%s --help' for more information.\n", prog_name(argv[0]));
            return(1);
         };
         cmd = REPATTERN_CMD_PRINT;
         break;

         case 'q':
         if ((verbose))
         {
            fprintf(stderr, "%s: conflicting options -- '-v' and '-q'\n", prog_name(argv[0]));
            fprintf(stderr, "Try `%s --help' for more information.\n", prog_name(argv[0]));
            return(1);
         };
         quiet++;
         break;

         case 'V':
         repattern_version(prog_name(argv[0]));
         return(0);

         case 'v':
         if ((quiet))
         {
            fprintf(stderr, "%s: conflicting options -- '-v' and '-q'\n", prog_name(argv[0]));
            fprintf(stderr, "Try `%s --help' for more information.\n", prog_name(argv[0]));
            return(1);
         };
         verbose++;
         break;

         default:
         if (c < 0x0100)
         {
            fprintf(stderr, "%s: invalid option -- %c\n", prog_name(argv[0]), c);
            fprintf(stderr, "Try `%s --help' for more information.\n", prog_name(argv[0]));
            return(-2);
         };
         reid = c;
         break;
      };
   };

   // verifies parsed options
   if (cmd == 0)
   {
      fprintf(stderr, "%s: must specify a command\n", prog_name(argv[0]));
      fprintf(stderr, "Try `%s --help' for more information.\n", prog_name(argv[0]));
      return(1);
   };
   if (reid == 0)
   {
      fprintf(stderr, "%s: must specify a pattern\n", prog_name(argv[0]));
      fprintf(stderr, "Try `%s --help' for more information.\n", prog_name(argv[0]));
      return(1);
   };

   // checks for required arguments to commands
   switch(cmd)
   {
      case REPATTERN_CMD_CONTAINS:
      case REPATTERN_CMD_IS:
      if (optind == argc)
      {
         fprintf(stderr, "%s: missing required argument for command\n", prog_name(argv[0]));
         fprintf(stderr, "Try `%s --help' for more information.\n", prog_name(argv[0]));
         return(1);
      };
      if ((optind+1) != argc)
      {
         fprintf(stderr, "%s: invalid arguments -- %s\n", prog_name(argv[0]), argv[optind+1]);
         fprintf(stderr, "Try `%s --help' for more information.\n", prog_name(argv[0]));
         return(1);
      };
      break;

      default:
      if ((optind) != argc)
      {
         fprintf(stderr, "%s: invalid arguments -- %s\n", prog_name(argv[0]), argv[optind]);
         fprintf(stderr, "Try `%s --help' for more information.\n", prog_name(argv[0]));
         return(1);
      };
      break;
   };

   err = 0;
   switch(cmd)
   {
      case REPATTERN_CMD_CONTAINS:
      nmatch = REPATTERN_MAX_MATCHES;
      err = repattern_contains(reid, argv[optind], &nmatch, matches, re_flags);

      if ((quiet))
         break;
      if ((err))
      {
         if (sub_index == -1)
            printf("not found\n");
         break;
      };

      if ( (verbose < 1) && (sub_index == -1) )
         printf("found\n");

      if (sub_index >= 0)
         if (sub_index < (ssize_t)nmatch)
            if ((len = repattern_cpymatch(str, 1024, argv[optind], &matches[sub_index])))
               printf("%s\n", str);

      repattern_verbose(verbose, reid, argv[optind], nmatch, matches);
      /*
      if (verbose > 0)
         if ((len = repattern_cpymatch(str, 1024, argv[optind], &matches[0])))
               printf("matched: %s\n", str);

      if (verbose > 1)
         for(c = 0; c < (int)nmatch; c++)
            if ((len = repattern_cpymatch(str, 1024, argv[optind], &matches[c])) > 0)
               printf("   submatch %i: %s\n", c, str);
      */
      break;

      case REPATTERN_CMD_IS:
      err = repattern_is(reid, argv[optind], &nmatch, matches, re_flags);
      if ((quiet))
         break;
      if (sub_index == -1)
      {
         if (!(err))
            printf("matched\n");
         else
            printf("not matched\n");
         break;
      };
      break;

      case REPATTERN_CMD_LIST_SUB:
      labels = repattern_labels(reid, &labels_len);
      if ((labels))
      {
         printf("Available Sub-matches:\n");
         for(c = 0; c < (int)labels_len; c++)
            printf("   submatch %i: %s\n", c, labels[c]);
      }
      else
      {
         fprintf(stderr, "%s: sub-matches unavailable for pattern\n", prog_name(argv[0]));
         return(1);
      };
      break;

      default:
      printf("%s\n", repattern_string(reid));
      break;
   };

   return(err != 0);
}


const char * prog_name(const char * name)
{
   const char * ptr;
   assert(name != NULL);
   if ((ptr = rindex(name, '/')) != NULL)
      return(&ptr[1]);
   return(name);
}


void repattern_usage(const char * name)
{
   printf(("Usage: %s [-s | --string ]   pattern [OPTIONS]\n"
         "       %s [-i | --is ]       pattern [OPTIONS] string\n"
         "       %s [-c | --contains ] pattern [OPTIONS] string\n"
         "Commands:\n"
         "  -c, --contains            attempts to find pattern withing string\n"
         "  -i, --is                  determines if string contains only pattern\n"
         "  -l, --list                list available submatches\n"
         "  -p, --print               display regular expression\n"
         "Options:\n"
         "  -h, --help                print this help and exit\n"
         "  -I                        ignore upper/lower case distinctions. (REG_ICASE)\n"
         "  -L                        enable newline-sensitive matching (REG_NEWLINE)\n"
         "  -q, --quiet, --silent     do not print messages\n"
         "  -s  index                 display submatch at index (--contains command only)\n"
         "  -v, --verbose             print verbose messages\n"
         "  -V, --version             print version number and exit\n"
         "Patterns:\n"
         "  --email-address\n"
         "  --host\n"
         "  --hostname\n"
         "  --ip-address\n"
         "  --ip-port\n"
         "  --ipv4-address\n"
         "  --ipv4-port\n"
         "  --ipv6-address\n"
         "  --ipv6-port\n"
         "\n"
         "Report bugs to <%s>.\n"
      ), name, name, name, PACKAGE_BUGREPORT
   );
   return;
}


void repattern_verbose(int verbose, int reid, const char * str, size_t nmatch,
   regmatch_t * matches)
{
   size_t        x;
   size_t        pos;
   int           len;
   int           slen;
   const char ** labels;
   size_t        labels_len;
   char          label[1024];
   char          buff[1024];

   if (verbose > 0)
      if ((repattern_cpymatch(buff, 1024, str, &matches[0])))
            printf("matched: %s\n", buff);

   if (verbose > 1)
   {
      len    = 0;
      labels = repattern_labels(reid, &labels_len);
      for(x = 0; x < 2; x++)
      {
         for(pos = 0; pos < nmatch; pos++)
         {
            if ((verbose > 2) && (pos < labels_len))
               slen = snprintf(label, 1024, "%zu. %s:", pos, labels[pos]);
            else
               slen = snprintf(label, 1024, "submodule %zu:", pos);
            if (x == 0)
               if (slen > len)
                  len = slen;
            if (x == 1)
               if (repattern_cpymatch(buff, 1024, str, &matches[pos]) > 0)
                  printf("   %-*s %s\n", len, label, buff);
         };
      };
   };

   return;
}


void repattern_version(const char * name)
{
   printf(("%s (%s) %s\n"
         "%s\n"
      ), name, PACKAGE_NAME, PACKAGE_VERSION, PACKAGE_COPYRIGHT
   );
   return;
}

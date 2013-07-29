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

#define REPATTERN_MAX_MATCHES    50


//////////////////
//              //
//  Prototypes  //
//              //
//////////////////

int main(int argc, char * argv[]);
const char * prog_name(const char * name);
void repattern_usage(const char * name);
void repattern_version(const char * name);


/////////////////
//             //
//  Functions  //
//             //
/////////////////

int main(int argc, char * argv[])
{
   int          cmd;
   int          reid;
   int          re_flags;
   int          c;
   int          long_optindex;
   int          err;
   int          quiet;
   int          verbose;
   size_t       nmatch;
   regmatch_t   matches[REPATTERN_MAX_MATCHES];
   const char * arg;
   char         str[1024];
   int          len;

   // getopt options
   static char   short_opt[] = "cdhIiLqpvV";
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

   quiet    = 0;
   verbose  = 0;
   re_flags = 0;
   cmd      = 0;
   reid     = 0;

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
         cmd = REPATTERN_CMD_CONTAINS;
         break;

         case 'h':
         repattern_usage(prog_name(argv[0]));
         return(0);

         case 'I':
         re_flags |= REG_ICASE;
         break;

         case 'i':
         cmd = REPATTERN_CMD_IS;
         break;

         case 'L':
         re_flags |= REG_NEWLINE;
         break;

         case 'p':
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

   if (cmd == 0)
   {
      fprintf(stderr, "%s: must specify a command\n", prog_name(argv[0]));
      fprintf(stderr, "Try `%s --help' for more information.\n", prog_name(argv[0]));
      return(1);
   };
   if ( ((cmd & 0x01)) && (optind == argc) )
   {
      fprintf(stderr, "%s: missing required argument for command\n", prog_name(argv[0]));
      fprintf(stderr, "Try `%s --help' for more information.\n", prog_name(argv[0]));
      return(1);
   };
   if ( ((cmd & 0x01)) && ((optind+1) != argc) )
   {
      fprintf(stderr, "%s: invalid arguments -- %s\n", prog_name(argv[0]), argv[optind+1]);
      fprintf(stderr, "Try `%s --help' for more information.\n", prog_name(argv[0]));
      return(1);
   };
   if (reid == 0)
   {
      fprintf(stderr, "%s: must specify a pattern\n", prog_name(argv[0]));
      fprintf(stderr, "Try `%s --help' for more information.\n", prog_name(argv[0]));
      return(1);
   };

   arg = argv[optind];

   err = 0;
   switch(cmd)
   {
      case REPATTERN_CMD_CONTAINS:
      if (verbose > 1)
         printf("regular expression: %s\n", repattern_string(reid));
      nmatch = REPATTERN_MAX_MATCHES;
      err = repattern_contains(reid, arg, &nmatch, matches, re_flags);
      if ((quiet))
         break;
      if ((err))
      {
         printf("not found\n");
         break;
      };
      if (verbose < 1)
         printf("found\n");
      if (verbose > 0)
      {
         if ((len = (int)(matches[0].rm_eo - matches[0].rm_so)) > 0)
         {
            memset(str, 0, 1024);
            strncpy(str, &arg[matches[0].rm_so], (size_t)len);
            if (verbose > 1)
               printf("match: ");
            printf("%s\n", str);
         };
      };
      if (verbose > 2)
      {
         for(c = 0; c < (int)nmatch; c++)
         {
            if ((len = (int)(matches[c].rm_eo - matches[c].rm_so)) > 0)
            {
               memset(str, 0, 1024);
               strncpy(str, &arg[matches[c].rm_so], (size_t)len);
               printf("submatch %i: %s\n", c, str);
            };
         };
      };
      break;

      case REPATTERN_CMD_IS:
      if (verbose > 2)
         printf("regular expression: %s\n", repattern_string(reid));
      err = repattern_is(reid, arg, re_flags);
      if (!(quiet))
      {
         if (!(err))
            printf("matched\n");
         else
            printf("not matched\n");
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
         "  -p, --print               display regular expression\n"
         "Options:\n"
         "  -h, --help                print this help and exit\n"
         "  -I                        ignore upper/lower case distinctions. (REG_ICASE)\n"
         "  -L                        enable newline-sensitive matching (REG_NEWLINE)\n"
         "  -q, --quiet, --silent     do not print messages\n"
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


void repattern_version(const char * name)
{
   printf(("%s (%s) %s\n"
         "%s\n"
      ), name, PACKAGE_NAME, PACKAGE_VERSION, PACKAGE_COPYRIGHT
   );
   return;
}

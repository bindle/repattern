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
/**
 */
#ifndef _LIBREPATTERN_RE_H
#define _LIBREPATTERN_RE_H 1

///////////////
//           //
//  Headers  //
//           //
///////////////

#include <repattern.h>
#include <stdio.h>
#include <pthread.h>
#include <regex.h>


//////////////////
//              //
//  Data Types  //
//              //
//////////////////

typedef struct
{
   pthread_mutex_t   mutex;
   int               initialized;
   int               flags;
   const char      * pattern;
} repattern_state;

#define REPATTERN_CONTAINS_STATE_INITIALIZER(pattern, flags) \
   { \
      PTHREAD_MUTEX_INITIALIZER, \
      0, \
      flags, \
      pattern, \
   }

#define REPATTERN_IS_STATE_INITIALIZER(pattern, flags) \
   { \
      PTHREAD_MUTEX_INITIALIZER, \
      0, \
      flags, \
      "^" pattern "$", \
   }

#define REPATTERN_CONTAINS_DEFAULT_FLAGS (REG_EXTENDED)
#define REPATTERN_IS_DEFAULT_FLAGS (REG_EXTENDED | REG_NOSUB)


typedef struct
{
   repattern_state   contains_state;
   repattern_state   is_state;
   regex_t         * preq;
   size_t            nsub;
   const char     ** subnames;
   const size_t    * subindexes;
} repattern_data;

#define REPATTERN_REGEX(pattern, flags) \
   { \
      PTHREAD_MUTEX_INITIALIZER, \
      0, \
      flags, \
      pattern, \
   }, \
   { \
      PTHREAD_MUTEX_INITIALIZER, \
      0, \
      flags, \
      "^" pattern "$", \
   }

//////////////////
//              //
//  Prototypes  //
//              //
//////////////////

int repattern_re(repattern_state * state, regex_t * preq,
   const char * str, size_t nsub, const size_t * subind, size_t * nmatchp,
   regmatch_t pmatch[], int flags);


#endif /* end of header */

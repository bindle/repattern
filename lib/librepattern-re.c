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
#include "librepattern-re.h"

///////////////
//           //
//  Headers  //
//           //
///////////////

#include <pthread.h>
#include <string.h>
#include <stdlib.h>


/////////////////
//             //
//  Functions  //
//             //
/////////////////


int repattern_re(repattern_state * state, regex_t * preq,
   const char * str, size_t nsub, const size_t * subind, size_t * nmatchp,
   regmatch_t pmatch[], int flags)
{
   int          err;
   regmatch_t * local_pmatch;
   size_t       local_nsub;
   size_t       size;
   size_t       nmatch;
   size_t       pos;

   // initializes regex and regex matches array
   pthread_mutex_lock(&state->mutex);
   if (!(state->initialized))
   {
      // compiles regugulare expressions
      if ((err = regcomp(preq, state->pattern, REG_EXTENDED)) != 0)
      {
         pthread_mutex_unlock(&state->mutex);
         return(err);
      };
      state->initialized++;
   };
   pthread_mutex_unlock(&state->mutex);

   // adjusts nsub
   if (nsub > preq->re_nsub)
      nsub = preq->re_nsub;

   // determines if submatches will be recorded
   nmatch       = 0;
   local_nsub   = 0;
   local_pmatch = NULL;
   if ((nmatchp))
   {
      // allocates memory for sub matches
      local_nsub  = preq->re_nsub;
      size        = sizeof(regmatch_t);
      size       *= local_nsub;
      if ((local_pmatch = malloc(size)) == NULL)
         return(REG_ESPACE);
      memset(local_pmatch, 0, size);

      // determines number of matches to record
      nmatch = *nmatchp;
      if ((*nmatchp > nsub) && (nsub > 0))
      {
         nmatch   = nsub;
         *nmatchp = nmatch;
      }
      else if (*nmatchp > preq->re_nsub)
      {
         nmatch   = preq->re_nsub;
         *nmatchp = nmatch;
      };
   };

   // executes regular expressions
   flags = 0;
   if ((err = regexec(preq, str, local_nsub, local_pmatch, flags)) != 0)
   {
      pthread_mutex_unlock(&state->mutex);
      return(err);
   };

   // copies result
   if ((local_pmatch))
   {
      if (nsub > 0)
      {
         size  = sizeof(regmatch_t);
         for(pos = 0; pos < nsub; pos++)
            memcpy(&pmatch[pos], &local_pmatch[subind[pos]], size);
      }
      else
      {
         size  = sizeof(regmatch_t);
         size *= nmatch;
         memcpy(pmatch, local_pmatch, size);
      };
   };

   if ((local_pmatch))
      free(local_pmatch);

   return(err);
}


 /* end of source */

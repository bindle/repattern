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
#include "librepattern-api.h"

///////////////
//           //
//  Headers  //
//           //
///////////////

#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "librepattern-re-net.h"


//////////////////
//              //
//  Prototypes  //
//              //
//////////////////

repattern_data * repattern_get_data(int reid);
repattern_data * repattern_get_ptr(int reid);


/////////////////
//             //
//  Functions  //
//             //
/////////////////

size_t repattern_cpymatch(char * s1, size_t n1, const char * s2,
   regmatch_t * match)
{
   size_t len;

   assert(s1    != NULL);
   assert(s2    != NULL);
   assert(n1     > 0);
   assert(match != NULL);
   assert(match->rm_eo >= match->rm_so);

   s1[0] = '\0';

   // calculate length of substring
   if ((len = (match->rm_eo - match->rm_so)) <= 0)
      return(0);
   len++;

   // calculates amount of match which can be copied into limited buffer
   if (n1 >= len)
      n1 = len - 1;

   // copies match
   memcpy(s1, &s2[match->rm_so], n1);
   s1[n1] = '\0';

   return(len);
}


repattern_data * repattern_get_ptr(int reid)
{
   assert(reid != 0);
   switch(reid)
   {
      // net
      case REPATTERN_RE_EMAIL_ADDRESS:    return(&repattern_email_address);
      case REPATTERN_RE_HOST:             return(&repattern_host);
      case REPATTERN_RE_HOSTNAME:         return(&repattern_hostname);
      case REPATTERN_RE_IP_ADDRESS:       return(&repattern_ip_address);
      case REPATTERN_RE_IP_PORT:          return(&repattern_ip_port);
      case REPATTERN_RE_IPV4_ADDRESS:     return(&repattern_ipv4_address);
      case REPATTERN_RE_IPV4_PORT:        return(&repattern_ipv4_port);
      case REPATTERN_RE_IPV6_ADDRESS:     return(&repattern_ipv6_address);
      case REPATTERN_RE_IPV6_PORT:        return(&repattern_ipv6_port);
      default:
      break;
   };
   return(NULL);
}


repattern_data * repattern_get_data(int reid)
{
   repattern_data * ptr;
   if ((ptr = repattern_get_ptr(reid)) == NULL)
      return(NULL);

   if (ptr->nsub == 0)
   {
      if ((ptr->subindexes))
         assert(ptr->subindexes[0] == 0);
      if ((ptr->subnames))
         assert(ptr->subnames[0] == NULL);
      return(ptr);
   };

   assert(ptr->subindexes[ptr->nsub] == 0);
   assert(ptr->subnames[ptr->nsub] == NULL);

   return(ptr);
}


int repattern_is(int reid, const char * str, int pflags)
{
   repattern_data * ptr;
   assert(reid != 0);
   assert(str  != NULL);
   if ((ptr = repattern_get_data(reid)) == NULL)
      return(REG_INVARG);
   return(repattern_re(&ptr->is_state, ptr->preq, str, 0, NULL, NULL, NULL, pflags));
}


int repattern_contains(int reid, const char * str, size_t * nmatchp,
   regmatch_t pmatch[], int pflags)
{
   repattern_data * ptr;
   assert(reid != 0);
   assert(str  != NULL);
   if ((ptr = repattern_get_data(reid)) == NULL)
      return(REG_INVARG);
   return(repattern_re(&ptr->contains_state, ptr->preq, str, ptr->nsub, ptr->subindexes, nmatchp, pmatch, pflags));
}


const char ** repattern_labels(int reid, size_t * nsubp)
{
   repattern_data * ptr;
   assert(reid != 0);
   if ((ptr = repattern_get_data(reid)) == NULL)
   {
      if ((nsubp))
         *nsubp = 0;
      return(NULL);
   };
   if ((nsubp))
      *nsubp = ptr->nsub;
   return(ptr->subnames);
}


const char * repattern_string(int reid)
{
   repattern_data * ptr;
   assert(reid != 0);
   if ((ptr = repattern_get_data(reid)) == NULL)
      return(NULL);
   return(ptr->contains_state.pattern);
}

 /* end of source */

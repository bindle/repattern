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
#include <assert.h>

#include "librepattern-re-net.h"


/////////////////
//             //
//  Functions  //
//             //
/////////////////

int repattern_is(int reid, const char * str, int pflags)
{
   assert(reid != 0);
   assert(str  != NULL);
   switch(reid)
   {
      // net
      case REPATTERN_RE_EMAIL_ADDRESS:    return(repattern_is_email_address(str, pflags));
      case REPATTERN_RE_HOST:             return(repattern_is_host(str, pflags));
      case REPATTERN_RE_HOSTNAME:         return(repattern_is_hostname(str, pflags));
      case REPATTERN_RE_IP_ADDRESS:       return(repattern_is_ip_address(str, pflags));
      case REPATTERN_RE_IP_PORT:          return(repattern_is_ip_port(str, pflags));
      case REPATTERN_RE_IPV4_ADDRESS:     return(repattern_is_ipv4_address(str, pflags));
      case REPATTERN_RE_IPV4_PORT:        return(repattern_is_ipv4_port(str, pflags));
      case REPATTERN_RE_IPV6_ADDRESS:     return(repattern_is_ipv6_address(str, pflags));
      case REPATTERN_RE_IPV6_PORT:        return(repattern_is_ipv6_port(str, pflags));
      default:
      break;
   };
   return(REG_INVARG);
}


int repattern_contains(int reid, const char * str, size_t * nmatchp,
   regmatch_t pmatch[], int pflags)
{
   assert(reid != 0);
   assert(str  != NULL);
   switch(reid)
   {
      // net
      case REPATTERN_RE_EMAIL_ADDRESS:    return(repattern_contains_email_address(str, nmatchp, pmatch, pflags));
      case REPATTERN_RE_HOST:             return(repattern_contains_host(str, nmatchp, pmatch, pflags));
      case REPATTERN_RE_HOSTNAME:         return(repattern_contains_hostname(str, nmatchp, pmatch, pflags));
      case REPATTERN_RE_IP_ADDRESS:       return(repattern_contains_ip_address(str, nmatchp, pmatch, pflags));
      case REPATTERN_RE_IP_PORT:          return(repattern_contains_ip_port(str, nmatchp, pmatch, pflags));
      case REPATTERN_RE_IPV4_ADDRESS:     return(repattern_contains_ipv4_address(str, nmatchp, pmatch, pflags));
      case REPATTERN_RE_IPV4_PORT:        return(repattern_contains_ipv4_port(str, nmatchp, pmatch, pflags));
      case REPATTERN_RE_IPV6_ADDRESS:     return(repattern_contains_ipv6_address(str, nmatchp, pmatch, pflags));
      case REPATTERN_RE_IPV6_PORT:        return(repattern_contains_ipv6_port(str, nmatchp, pmatch, pflags));
      default:
      break;
   };
   return(REG_INVARG);
}


const char * repattern_string(int reid)
{
   assert(reid != 0);
   switch(reid)
   {
      // net
      case REPATTERN_RE_EMAIL_ADDRESS:    return(REPATTERN_EMAIL_ADDRESS);
      case REPATTERN_RE_HOST:             return(REPATTERN_HOST);
      case REPATTERN_RE_HOSTNAME:         return(REPATTERN_HOSTNAME);
      case REPATTERN_RE_IP_ADDRESS:       return(REPATTERN_IP_ADDRESS);
      case REPATTERN_RE_IP_PORT:          return(REPATTERN_IP_PORT);
      case REPATTERN_RE_IPV4_ADDRESS:     return(REPATTERN_IPV4_ADDRESS);
      case REPATTERN_RE_IPV4_PORT:        return(REPATTERN_IPV4_PORT);
      case REPATTERN_RE_IPV6_ADDRESS:     return(REPATTERN_IPV6_ADDRESS);
      case REPATTERN_RE_IPV6_PORT:        return(REPATTERN_IPV6_PORT);
      default:
      break;
   };
   return(NULL);
}

 /* end of source */

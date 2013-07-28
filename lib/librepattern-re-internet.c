/*
 *  Repattern Library
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
#include "librepattern-re-internet.h"

///////////////
//           //
//  Headers  //
//           //
///////////////

#include <stdio.h>
#include "librepattern-re.h"


/////////////////
//             //
//  Functions  //
//             //
/////////////////

int repattern_contains_email_address(const char * str, size_t * nmatchp, regmatch_t pmatch[], int re_flags)
{
   repattern_state  state = REPATTERN_CONTAINS_STATE_INITIALIZER(REPATTERN_EMAIL_ADDRESS, REPATTERN_DEFAULT_FLAGS);
   static regex_t   req;
   return(repattern_re(&state, &req, str, nmatchp, pmatch, re_flags));
}


int repattern_contains_host(const char * str, size_t * nmatchp, regmatch_t pmatch[], int re_flags)
{
   repattern_state  state = REPATTERN_CONTAINS_STATE_INITIALIZER(REPATTERN_HOST, REPATTERN_DEFAULT_FLAGS);
   static regex_t   req;
   return(repattern_re(&state, &req, str, nmatchp, pmatch, re_flags));
}


int repattern_contains_hostname(const char * str, size_t * nmatchp, regmatch_t pmatch[], int re_flags)
{
   repattern_state  state = REPATTERN_CONTAINS_STATE_INITIALIZER(REPATTERN_HOSTNAME, REPATTERN_DEFAULT_FLAGS);
   static regex_t   req;
   return(repattern_re(&state, &req, str, nmatchp, pmatch, re_flags));
}


int repattern_contains_ip_address(const char * str, size_t * nmatchp, regmatch_t pmatch[], int re_flags)
{
   repattern_state  state = REPATTERN_CONTAINS_STATE_INITIALIZER(REPATTERN_IP_ADDRESS, REPATTERN_DEFAULT_FLAGS);
   static regex_t   req;
   return(repattern_re(&state, &req, str, nmatchp, pmatch, re_flags));
}


int repattern_contains_ip_port(const char * str, size_t * nmatchp, regmatch_t pmatch[], int re_flags)
{
   repattern_state  state = REPATTERN_CONTAINS_STATE_INITIALIZER(REPATTERN_IP_PORT, REPATTERN_DEFAULT_FLAGS);
   static regex_t   req;
   return(repattern_re(&state, &req, str, nmatchp, pmatch, re_flags));
}


int repattern_contains_ipv4_address(const char * str, size_t * nmatchp, regmatch_t pmatch[], int re_flags)
{
   repattern_state  state = REPATTERN_CONTAINS_STATE_INITIALIZER(REPATTERN_IPV4_ADDRESS, REPATTERN_DEFAULT_FLAGS);
   static regex_t   req;
   return(repattern_re(&state, &req, str, nmatchp, pmatch, re_flags));
}


int repattern_contains_ipv4_port(const char * str, size_t * nmatchp, regmatch_t pmatch[], int re_flags)
{
   repattern_state  state = REPATTERN_CONTAINS_STATE_INITIALIZER(REPATTERN_IPV4_PORT, REPATTERN_DEFAULT_FLAGS);
   static regex_t   req;
   return(repattern_re(&state, &req, str, nmatchp, pmatch, re_flags));
}


int repattern_contains_ipv6_address(const char * str, size_t * nmatchp, regmatch_t pmatch[], int re_flags)
{
   repattern_state  state = REPATTERN_CONTAINS_STATE_INITIALIZER(REPATTERN_IPV6_ADDRESS, REPATTERN_DEFAULT_FLAGS);
   static regex_t   req;
   return(repattern_re(&state, &req, str, nmatchp, pmatch, re_flags));
}


int repattern_contains_ipv6_port(const char * str, size_t * nmatchp, regmatch_t pmatch[], int re_flags)
{
   repattern_state  state = REPATTERN_CONTAINS_STATE_INITIALIZER(REPATTERN_IPV6_PORT, REPATTERN_DEFAULT_FLAGS);
   static regex_t   req;
   return(repattern_re(&state, &req, str, nmatchp, pmatch, re_flags));
}


//////////////////////
//                  //
//  "is" Functions  //
//                  //
//////////////////////

int repattern_is_email_address(const char * str, int re_flags)
{
   repattern_state  state = REPATTERN_IS_STATE_INITIALIZER(REPATTERN_EMAIL_ADDRESS, REPATTERN_DEFAULT_FLAGS);
   static regex_t   req;
   return(repattern_re(&state, &req, str, NULL, NULL, re_flags));
}


int repattern_is_host(const char * str, int re_flags)
{
   repattern_state  state = REPATTERN_IS_STATE_INITIALIZER(REPATTERN_HOST, REPATTERN_DEFAULT_FLAGS);
   static regex_t   req;
   return(repattern_re(&state, &req, str, NULL, NULL, re_flags));
}


int repattern_is_hostname(const char * str, int re_flags)
{
   repattern_state  state = REPATTERN_IS_STATE_INITIALIZER(REPATTERN_HOSTNAME, REPATTERN_DEFAULT_FLAGS);
   static regex_t   req;
   return(repattern_re(&state, &req, str, NULL, NULL, re_flags));
}


int repattern_is_ip_address(const char * str, int re_flags)
{
   repattern_state  state = REPATTERN_IS_STATE_INITIALIZER(REPATTERN_IP_ADDRESS, REPATTERN_DEFAULT_FLAGS);
   static regex_t   req;
   return(repattern_re(&state, &req, str, NULL, NULL, re_flags));
}


int repattern_is_ip_port(const char * str, int re_flags)
{
   repattern_state  state = REPATTERN_IS_STATE_INITIALIZER(REPATTERN_IP_PORT, REPATTERN_DEFAULT_FLAGS);
   static regex_t   req;
   return(repattern_re(&state, &req, str, NULL, NULL, re_flags));
}


int repattern_is_ipv4_address(const char * str, int re_flags)
{
   repattern_state  state = REPATTERN_IS_STATE_INITIALIZER(REPATTERN_IPV4_ADDRESS, REPATTERN_DEFAULT_FLAGS);
   static regex_t   req;
   return(repattern_re(&state, &req, str, NULL, NULL, re_flags));
}


int repattern_is_ipv4_port(const char * str, int re_flags)
{
   repattern_state  state = REPATTERN_IS_STATE_INITIALIZER(REPATTERN_IPV4_PORT, REPATTERN_DEFAULT_FLAGS);
   static regex_t   req;
   return(repattern_re(&state, &req, str, NULL, NULL, re_flags));
}


int repattern_is_ipv6_address(const char * str, int re_flags)
{
   repattern_state  state = REPATTERN_IS_STATE_INITIALIZER(REPATTERN_IPV6_ADDRESS, REPATTERN_DEFAULT_FLAGS);
   static regex_t   req;
   return(repattern_re(&state, &req, str, NULL, NULL, re_flags));
}


int repattern_is_ipv6_port(const char * str, int re_flags)
{
   repattern_state  state = REPATTERN_IS_STATE_INITIALIZER(REPATTERN_IPV6_PORT, REPATTERN_DEFAULT_FLAGS);
   static regex_t   req;
   return(repattern_re(&state, &req, str, NULL, NULL, re_flags));
}

/* end of source */

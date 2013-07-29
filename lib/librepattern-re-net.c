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
#include "librepattern-re-net.h"

///////////////
//           //
//  Headers  //
//           //
///////////////

#include <stdio.h>


/////////////////
//             //
//  Functions  //
//             //
/////////////////

static regex_t repattern_regex_email_address;
repattern_data repattern_email_address =
{
   REPATTERN_CONTAINS_STATE_INITIALIZER(REPATTERN_EMAIL_ADDRESS, REPATTERN_CONTAINS_DEFAULT_FLAGS),
   REPATTERN_IS_STATE_INITIALIZER(REPATTERN_EMAIL_ADDRESS, REPATTERN_IS_DEFAULT_FLAGS),
   &repattern_regex_email_address,
   0, NULL, NULL
};


static regex_t repattern_regex_host;
repattern_data repattern_host =
{
   REPATTERN_CONTAINS_STATE_INITIALIZER(REPATTERN_HOST, REPATTERN_CONTAINS_DEFAULT_FLAGS),
   REPATTERN_IS_STATE_INITIALIZER(REPATTERN_HOST, REPATTERN_IS_DEFAULT_FLAGS),
   &repattern_regex_host,
   0, NULL, NULL
};


static regex_t repattern_regex_hostname;
repattern_data repattern_hostname =
{
   REPATTERN_CONTAINS_STATE_INITIALIZER(REPATTERN_HOSTNAME, REPATTERN_CONTAINS_DEFAULT_FLAGS),
   REPATTERN_IS_STATE_INITIALIZER(REPATTERN_HOSTNAME, REPATTERN_IS_DEFAULT_FLAGS),
   &repattern_regex_hostname,
   0, NULL, NULL
};


static regex_t repattern_regex_ip_address;
repattern_data repattern_ip_address =
{
   REPATTERN_CONTAINS_STATE_INITIALIZER(REPATTERN_IP_ADDRESS, REPATTERN_CONTAINS_DEFAULT_FLAGS),
   REPATTERN_IS_STATE_INITIALIZER(REPATTERN_IP_ADDRESS, REPATTERN_IS_DEFAULT_FLAGS),
   &repattern_regex_ip_address,
   0, NULL, NULL
};


static regex_t repattern_regex_ip_port;
repattern_data repattern_ip_port =
{
   REPATTERN_CONTAINS_STATE_INITIALIZER(REPATTERN_IP_PORT, REPATTERN_CONTAINS_DEFAULT_FLAGS),
   REPATTERN_IS_STATE_INITIALIZER(REPATTERN_IP_PORT, REPATTERN_IS_DEFAULT_FLAGS),
   &repattern_regex_ip_port,
   0, NULL, NULL
};


static regex_t repattern_regex_ipv4_address;
repattern_data repattern_ipv4_address =
{
   REPATTERN_CONTAINS_STATE_INITIALIZER(REPATTERN_IPV4_ADDRESS, REPATTERN_CONTAINS_DEFAULT_FLAGS),
   REPATTERN_IS_STATE_INITIALIZER(REPATTERN_IPV4_ADDRESS, REPATTERN_IS_DEFAULT_FLAGS),
   &repattern_regex_ipv4_address,
   0, NULL, NULL
};


static regex_t repattern_regex_ipv4_port;
repattern_data repattern_ipv4_port =
{
   REPATTERN_CONTAINS_STATE_INITIALIZER(REPATTERN_IPV6_ADDRESS, REPATTERN_CONTAINS_DEFAULT_FLAGS),
   REPATTERN_IS_STATE_INITIALIZER(REPATTERN_IPV6_ADDRESS, REPATTERN_IS_DEFAULT_FLAGS),
   &repattern_regex_ipv4_port,
   0, NULL, NULL
};


static regex_t repattern_regex_ipv6_address;
repattern_data repattern_ipv6_address =
{
   REPATTERN_CONTAINS_STATE_INITIALIZER(REPATTERN_IPV6_ADDRESS, REPATTERN_CONTAINS_DEFAULT_FLAGS),
   REPATTERN_IS_STATE_INITIALIZER(REPATTERN_IPV6_ADDRESS, REPATTERN_IS_DEFAULT_FLAGS),
   &repattern_regex_ipv6_address,
   //0, NULL, NULL
   3,
   (const char *[5]){  "IP Address", "Link-local Address", "Link-local Zone", NULL},
   (const size_t [5]){ 0,            17,                   19,                0 }
};


static regex_t repattern_regex_ipv6_port;
repattern_data repattern_ipv6_port =
{
   REPATTERN_CONTAINS_STATE_INITIALIZER(REPATTERN_IPV6_ADDRESS, REPATTERN_CONTAINS_DEFAULT_FLAGS),
   REPATTERN_IS_STATE_INITIALIZER(REPATTERN_IPV6_ADDRESS, REPATTERN_IS_DEFAULT_FLAGS),
   &repattern_regex_ipv6_port,
   0, NULL, NULL
};


/* end of source */

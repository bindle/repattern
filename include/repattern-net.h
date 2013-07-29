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
#ifndef _REPATTERN_NET_H
#define _REPATTERN_NET_H 1

///////////////
//           //
//  Headers  //
//           //
///////////////

#include <inttypes.h>


///////////////////
//               //
//  Definitions  //
//               //
///////////////////

// internet patterns
#define REPATTERN_CAT_NET              0x00010000
#define REPATTERN_RE_EMAIL_ADDRESS     (1 + REPATTERN_CAT_NET)
#define REPATTERN_RE_HOST              (2 + REPATTERN_CAT_NET)
#define REPATTERN_RE_HOSTNAME          (3 + REPATTERN_CAT_NET)
#define REPATTERN_RE_IP_ADDRESS        (4 + REPATTERN_CAT_NET)
#define REPATTERN_RE_IP_PORT           (5 + REPATTERN_CAT_NET)
#define REPATTERN_RE_IPV4_ADDRESS      (6 + REPATTERN_CAT_NET)
#define REPATTERN_RE_IPV4_PORT         (7 + REPATTERN_CAT_NET)
#define REPATTERN_RE_IPV6_ADDRESS      (8 + REPATTERN_CAT_NET)
#define REPATTERN_RE_IPV6_PORT         (9 + REPATTERN_CAT_NET)
#define REPATTERN_RE_URL               (10 + REPATTERN_CAT_NET)


///////////////////////////
//                       //
//  Regular Expressions  //
//                       //
///////////////////////////

/**
 *  Regular expression for IPv4 address.
 */
#define REPATTERN_IPV4_ADDRESS  \
   "(" \
   "(25[0-5]|(2[0-4]|1{0,1}[0-9]){0,1}[0-9])\\." \
   "(25[0-5]|(2[0-4]|1{0,1}[0-9]){0,1}[0-9])\\." \
   "(25[0-5]|(2[0-4]|1{0,1}[0-9]){0,1}[0-9])\\." \
   "(25[0-5]|(2[0-4]|1{0,1}[0-9]){0,1}[0-9])" \
   ")"


/**
 *  Regular expression for IPv6 address.
 */
#define REPATTERN_IPV6_ADDRESS  \
   "(" \
   "([0-9a-f]{1,4}:){7,7}[0-9a-f]{1,4}|"                     /* 1:2:3:4:5:6:7:8                                  */ \
   "([0-9a-f]{1,4}:){1,7}:|"                                 /* 1::                              1:2:3:4:5:6:7:: */ \
   "([0-9a-f]{1,4}:){1,6}:[0-9a-f]{1,4}|"                    /* 1::8             1:2:3:4:5:6::8  1:2:3:4:5:6::8  */ \
   "([0-9a-f]{1,4}:){1,5}(:[0-9a-f]{1,4}){1,2}|"             /* 1::7:8           1:2:3:4:5::7:8  1:2:3:4:5::8    */ \
   "([0-9a-f]{1,4}:){1,4}(:[0-9a-f]{1,4}){1,3}|"             /* 1::6:7:8         1:2:3:4::6:7:8  1:2:3:4::8      */ \
   "([0-9a-f]{1,4}:){1,3}(:[0-9a-f]{1,4}){1,4}|"             /* 1::5:6:7:8       1:2:3::5:6:7:8  1:2:3::8        */ \
   "([0-9a-f]{1,4}:){1,2}(:[0-9a-f]{1,4}){1,5}|"             /* 1::4:5:6:7:8     1:2::4:5:6:7:8  1:2::8          */ \
   "[0-9a-f]{1,4}:((:[0-9a-f]{1,4}){1,6})|"                  /* 1::3:4:5:6:7:8   1::3:4:5:6:7:8  1::8            */ \
   ":((:[0-9a-f]{1,4}){1,7}|:)|"                             /* ::2:3:4:5:6:7:8  ::2:3:4:5:6:7:8 ::8       ::    */ \
   "(fe80:(:[0-9a-f]{1,4}){1,4})%([0-9a-zA-Z]{1,}){0,1}|"    /* fe80::7:8%eth0   fe80::7:8%1     (link-local IPv6 addresses with zone index) */ \
   "(([0-9a-f]{1,4}:){1,4}|:(:ffff(:0{1,4}){0,1}){0,1}):" REPATTERN_IPV4_ADDRESS /* 2001:db8:3:4::192.0.2.33  64:ff9b::192.0.2.33 ::255.255.255.255   ::ffff:255.255.255.255  ::ffff:0:255.255.255.255  (IPv4-Embedded IPv6 Addresses, IPv4-mapped IPv6 addresses and IPv4-translated addresses) */ \
   ")"


/**
 *  Regular expression for IP port.
 */
#define REPATTERN_IP_PORT "([0-9]{1,})"
#define REPATTERN_IPV4_PORT REPATTERN_IP_PORT
#define REPATTERN_IPV6_PORT REPATTERN_IP_PORT


/**
 *  Regular expression for IP address.
 */
#define REPATTERN_IP_ADDRESS "(" REPATTERN_IPV4_ADDRESS "|" REPATTERN_IPV6_ADDRESS ")"


/**
 *  Regular expression for DNS hostname.
 */
#define REPATTERN_HOSTNAME \
   "([0-9a-z]{1,}([-][0-9a-z]{1,}){0,}" \
   "(\\.[0-9a-z]{1,}([-][0-9a-z]{1,}){0,}){0,})"


/**
 *  Regular expression for host (including DNS host names and IP addresses).
 */
#define REPATTERN_HOST \
   "(" REPATTERN_HOSTNAME "|" REPATTERN_IPV4_ADDRESS "|" REPATTERN_IPV6_ADDRESS ")"


/**
 *  Regular expression for e-mail address.
 */
#define REPATTERN_EMAIL_ADDRESS \
   "(" \
   "[a-zA-Z0-9]{1,}([-_.]{1,}[a-zA-Z0-9]{1,}){0,}" \
   "(+([a-zA-Z0-9]{1,}([-_.]{1,}[a-zA-Z0-9]{1,}){0,}){0,1}@" \
   REPATTERN_HOSTNAME \
   ")"


#endif /* end of header */


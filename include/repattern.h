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
#ifndef _REPATTERN_H
#define _REPATTERN_H 1

///////////////
//           //
//  Headers  //
//           //
///////////////

#include <inttypes.h>
#include <regex.h>
#include <repattern-strings.h>


///////////////////
//               //
//  Definitions  //
//               //
///////////////////

// internet patterns
#define REPATTERN_RE_EMAIL_ADDRESS     0x0100
#define REPATTERN_RE_HOST              0x0101
#define REPATTERN_RE_HOSTNAME          0x0102
#define REPATTERN_RE_IP_ADDRESS        0x0103
#define REPATTERN_RE_IP_PORT           0x0104
#define REPATTERN_RE_IPV4_ADDRESS      0x0105
#define REPATTERN_RE_IPV4_PORT         0x0106
#define REPATTERN_RE_IPV6_ADDRESS      0x0107
#define REPATTERN_RE_IPV6_PORT         0x0108
#define REPATTERN_RE_URL               0x0109


//////////////////
//              //
//  Prototypes  //
//              //
//////////////////

// package information functions
const char * repattern_build(void);
const char * repattern_build_version(void);
float        repattern_version_number(void);
const char * repattern_version_string(void);

// api information functions
int          repattern_api_age(void);
int          repattern_api_current(void);
int          repattern_api_revision(void);
const char * repattern_api_release_info(void);
const char * repattern_api_version_info(void);

// regex functions
int repattern_is(int reid, const char * str, int pflags);
int repattern_contains(int reid, const char * str, size_t * nmatchp,
   regmatch_t pmatch[], int pflags);
const char * repattern_string(int reid);

#endif /* end of header */

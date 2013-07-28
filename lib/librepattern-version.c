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
#include "librepattern-version.h"

///////////////
//           //
//  Headers  //
//           //
///////////////

#ifdef HAVE_CONFIG_H
#   include "config.h"
#endif
#ifdef USE_XCODE
#   include "REPattern/git-package-version.h"
#endif


//////////////
//          //
//  Macros  //
//          //
//////////////

#ifndef   GIT_PACKAGE_BUILD
#define   GIT_PACKAGE_BUILD ""
#endif
#ifndef   GIT_PACKAGE_VERSION
#define   GIT_PACKAGE_VERSION ""
#endif
#ifndef   GIT_PACKAGE_NUMERIC_VERSION
#define   GIT_PACKAGE_NUMERIC_VERSION 0.0f
#endif
#ifndef   GIT_PACKAGE_STRING
#define   GIT_PACKAGE_STRING ""
#endif


#ifndef   LIB_VERSION_AGE
#define   LIB_VERSION_AGE -1
#endif
#ifndef   LIB_VERSION_CURRENT
#define   LIB_VERSION_CURRENT -1
#endif
#ifndef   LIB_VERSION_REVISION
#define   LIB_VERSION_REVISION -1
#endif
#ifndef   LIB_RELEASE_INFO
#define   LIB_RELEASE_INFO "-1:0:0"
#endif
#ifndef   LIB_VERSION_INFO
#define   LIB_VERSION_INFO "-1:0:0"
#endif


/////////////////
//             //
//  Functions  //
//             //
/////////////////

const char * repattern_build(void)           { return(GIT_PACKAGE_BUILD); }
const char * repattern_build_version(void)   { return(GIT_PACKAGE_VERSION); }
float        repattern_version_number(void)  { return(GIT_PACKAGE_NUMERIC_VERSION); }
const char * repattern_version_string(void)  { return(GIT_PACKAGE_STRING); }


int          repattern_api_age(void)           { return(LIB_VERSION_AGE); }
int          repattern_api_current(void)       { return(LIB_VERSION_CURRENT); }
int          repattern_api_revision(void)      { return(LIB_VERSION_REVISION); }
const char * repattern_api_release_info(void)  { return(LIB_RELEASE_INFO); }
const char * repattern_api_version_info(void)  { return(LIB_VERSION_INFO); }


 /* end of source */

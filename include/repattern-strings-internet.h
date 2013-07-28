////////////////
//            //
//  Internet  //
//            //
////////////////

/**
 *  Regular expression for IPv4 address.
 */
#define REPATTERN_IPV4_ADDRESS  \
   "((25[0-5]|(2[0-4]|1{0,1}[0-9]){0,1}[0-9])\\.){3,3}" \
   "(25[0-5]|(2[0-4]|1{0,1}[0-9]){0,1}[0-9])"


/**
 *  Regular expression for IPv6 address.
 */
#define REPATTERN_IPV6_ADDRESS  \
   "(" \
   "([0-9a-f]{1,4}:){7,7}[0-9a-f]{1,4}|"                 /* 1:2:3:4:5:6:7:8                                  */ \
   "([0-9a-f]{1,4}:){1,7}:|"                             /* 1::                              1:2:3:4:5:6:7:: */ \
   "([0-9a-f]{1,4}:){1,6}:[0-9a-f]{1,4}|"                /* 1::8             1:2:3:4:5:6::8  1:2:3:4:5:6::8  */ \
   "([0-9a-f]{1,4}:){1,5}(:[0-9a-f]{1,4}){1,2}|"         /* 1::7:8           1:2:3:4:5::7:8  1:2:3:4:5::8    */ \
   "([0-9a-f]{1,4}:){1,4}(:[0-9a-f]{1,4}){1,3}|"         /* 1::6:7:8         1:2:3:4::6:7:8  1:2:3:4::8      */ \
   "([0-9a-f]{1,4}:){1,3}(:[0-9a-f]{1,4}){1,4}|"         /* 1::5:6:7:8       1:2:3::5:6:7:8  1:2:3::8        */ \
   "([0-9a-f]{1,4}:){1,2}(:[0-9a-f]{1,4}){1,5}|"         /* 1::4:5:6:7:8     1:2::4:5:6:7:8  1:2::8          */ \
   "[0-9a-f]{1,4}:((:[0-9a-f]{1,4}){1,6})|"              /* 1::3:4:5:6:7:8   1::3:4:5:6:7:8  1::8            */ \
   ":((:[0-9a-f]{1,4}){1,7}|:)|"                         /* ::2:3:4:5:6:7:8  ::2:3:4:5:6:7:8 ::8       ::    */ \
   "fe80:(:[0-9a-f]{1,4}){1,4}%[0-9a-zA-Z]{1,}|"         /* fe80::7:8%eth0   fe80::7:8%1     (link-local IPv6 addresses with zone index) */ \
   "::(ffff(:0{1,4}){0,1}:){0,1}" REPATTERN_IPV4_ADDRESS /* ::255.255.255.255   ::ffff:255.255.255.255  ::ffff:0:255.255.255.255  (IPv4-mapped IPv6 addresses and IPv4-translated addresses) */ \
   "([0-9a-f]{1,4}:){1,4}:" REPATTERN_IPV4_ADDRESS       /* 2001:db8:3:4::192.0.2.33  64:ff9b::192.0.2.33 (IPv4-Embedded IPv6 Address)  */ \
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

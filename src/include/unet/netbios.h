/**
 * NetBIOS over TCP/IP protocols, as defined by RFC 1002.
 */

#ifndef __UNET_NETBIOS_H__
#define __UNET_NETBIOS_H__

#include "types.h"

struct netbios_name_service_hdr {
        word    name_trn_id;
        byte    opcode:5;
        byte    nm_flags:7;
        byte    rcode:4;
        word    qdcount;
        word    ancount;
        word    nscount;
        word    arcount;
};

struct netbios_name_service_question {
        byte    *name;
        word     type;
        word     class;
};

struct netbios_name_service_rrecord {
        byte    *name;
        word     type;
        word     class;
        dword    ttl;
        word     length;
        byte     *data;
};

/**
 * Though a NetBIOS session service packet does not TECHNICALLY have a header,
 * all packets begin with a type-flags-length segment that is functionally
 * identical to a header. It is this segment that the following struct
 * describes.
 */
struct netbios_session_service_hdr {
        byte    type;
        byte    flags;
        word    length;
};

struct netbios_datagram_service_hdr {
        byte    type;
        byte    flags;
        word    dgm_id;
        dword   src_addr;
        word    src_port;
        word    dgm_length;
        word    offset;
};

#endif //__UNET_NETBIOS_H__
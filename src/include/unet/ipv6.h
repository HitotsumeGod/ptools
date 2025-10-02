#ifndef __UNET_IPV6_H__
#define __UNET_IPV6_H__

struct ipv6_hdr {
        byte        version:4;
        byte        tclass;
        byte        flow1:4;
        word        flow2;
        word        length;
        byte        nxt_hdr;
        byte        hop_lim;
        dword       src_addr[4];
        dword       dest_addr[4];
};

/**
 * Given that both adhere to this structure, this struct may be used to hold both an IPv6 Hop-by-Hop Options Header AND an IPv6 Destination Options Header.
 */
struct ipv6_ext_opts_hdr {
        byte        nxt_hdr;
        byte        length;
        struct {
                byte        type;
                byte        len;
                byte        *data;
        } *opts;
};

struct ipv6_ext_routing_hdr {
        byte        nxt_hdr;
        byte        length;
        byte        type;
        byte        seg_left;
        byte        *data;
};

struct ipv6_ext_frag_hdr {
        byte        nxt_hdr;
        byte        reserved;
        byte        frag_off1;
        byte        frag_off2:5;
        byte        res:2;
        byte        m:1;
        dword       id;
};

#endif //__UNET_IPV6_H__

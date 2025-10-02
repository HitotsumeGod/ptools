#ifndef __UNET_IP_H__
#define __UNET_IP_H__

struct ip_hdr {
        byte        version:4;
        byte        ihl:4;
        byte        tos;
        word        tot_len;
        word        id;
        byte        flags:3;
        byte        frag_off1:5;
        byte        frag_off2;
        byte        ttl;
        byte        protocol;
        word        cksum;
        dword       src_addr;
        dword       dest_addr;
};

#endif //__UNET_IP_H__

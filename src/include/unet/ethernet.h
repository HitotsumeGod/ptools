#ifndef __UNET_ETHERNET_H__
#define __UNET_ETHERNET_H__

struct ieee8023_hdr {
        byte        src_addr[6];
        byte        dest_addr[6];
        word        length;
};

struct etherii_hdr {
        byte        src_addr[6];
        byte        dest_addr[6];
        word        ethertype;
};

#endif //__UNET_ETHERNET_H__

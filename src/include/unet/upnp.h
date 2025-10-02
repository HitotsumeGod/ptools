#ifndef __UNET_UPNP_H__
#define __UNET_UPNP_H__

struct upnp_ssdp_hdr {
        char *startline;
        struct {
                char *name;
                char *value;
        } hdr_field;
};

#endif //__UNET_UPNP_H__
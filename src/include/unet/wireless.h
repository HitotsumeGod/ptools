#ifndef __UNET_WIRELESS_H__
#define __UNET_WIRELESS_H__

struct ieee80211_hdr {
        struct {
                byte            proto_vers:2;
                byte            type:2;
                byte            subtype:4;
                byte            to_ds:1;
                byte            from_ds:1;
                byte            more_frag:1;
                byte            retry:1;
                byte            power_mng:1;
                byte            more_data:1;
                byte            prot_frame:1;
                byte            order:1;
        } *frame_control;
        word                    duration;
        byte                    addr1[6];
        byte                    addr2[6];
        byte                    addr3[6];
        word                    seq_ctrl;
        byte                    addr4[6];
};

#endif //__UNET_WIRELESS_H__

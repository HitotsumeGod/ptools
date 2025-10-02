/**
 * Universal Network header. Should eventually provide OSI-nested structs for every network protocol I can discover.
 * Should also contain relevant protocol constants.
 * The final goal is to be somewhat platform independent, allowing Windows developers to have the kind of network
 * struct access that Linux ones always have had, without having to rely on Wireshark. In the service of this goal,
 * this header MUST adhere to LLVM's clang compilation standards.
 */

#ifndef __UNET_H__
#define __UNET_H__

#include "types.h"
#include "unet/ethernet.h"
#include "unet/ieee80211.h"
#include "unet/ipv6.h"

struct network_dgram {
        union {
                struct iphdr            *iph;
                struct ip6hdr           *ip6h;
                struct arphdr           *arph;
        } *hdr;
        struct {
                union {
                        struct icpmhdr          *icmph;
                        struct icmp6hdr         *icmp6h;
                        struct tcphdr           *tcph;
                        struct udphdr           *udph;
                } *hdr;
                struct {
                        //NetBIOS Name Service
                        //NetBIOS Datagram Service
                        //NetBIOS Session Service
                        //Multicast Domain Name System
                        //Link-Local Domain Name Resolution
                        //Simple Service Discovery Protocol
                } l5_pkt;
        } transport_packet;
};

union linklayer_frame {
        struct {
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
                struct network_dgram    *body;
                dword                   fcs;
        } _80211_frame;
        struct {
                struct ethhdr           *hdr;
                struct network_dgram    *body;
                dword                   crc;
        } etherii_frame;
};

#endif //__UNET_H__

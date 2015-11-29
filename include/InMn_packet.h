/*
 * File: InMn_packet.h
 *
 * Author: Kaushik, Koneru
 *
 * Email: konerukaushik@gmail.com
 *
 * In this File we maintain Packet related information
 * like Ethernet, IP, TCP. As we use this information to store information
 * MAC (SRC,DST), IP (SRC,DST)
 */

#ifndef _INMN_PACKET_H_
#define _INMN_PACKET_H_

/* Ethernet Header Size is always 14 bytes */
#define ETHERNET_HEADER_SIZE 14 


/* Ethernet Address are of 6 bytes */
#define ETHERNET_ADDRS_LEN 6

/* Ethernet Header */
/*
 * ether_dhost --> Contains Ethernet Destination MAC Address
 * ether_shost --> Contains Ethernet Source MAC Address
 * ether_type  --> Contains EtherType like IP, ARP, RARP
 */
struct ethernet_header {
    u_int8_t  ether_dhost[ETHERNET_ADDRS_LEN];
    u_int8_t  ether_shost[ETHERNET_ADDRS_LEN];
    u_int16_t ether_type;
};

/* IP Header */
struct ip_header {
#if 0
#if __BYTE_ORDER == __LITTLE_ENDIAN
    unsigned int ip_hl:4;       /* header length */
    unsigned int ip_v:4;        /* version */
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
    unsigned int ip_v:4;        /* version */
    unsigned int ip_hl:4;       /* header length */
#endif
#endif
    u_char   ip_vhl;
    u_int8_t ip_tos;            /* type of service */
    u_short ip_len;         /* total length */
    u_short ip_id;          /* identification */
    u_short ip_off;         /* fragment offset field */
#define IP_RF 0x8000            /* reserved fragment flag */
#define IP_DF 0x4000            /* dont fragment flag */
#define IP_MF 0x2000            /* more fragments flag */
#define IP_OFFMASK 0x1fff       /* mask for fragmenting bits */
    u_int8_t ip_ttl;            /* time to live */
    u_int8_t ip_p;          /* protocol */
    u_short ip_sum;         /* checksum */
    struct in_addr ip_src, ip_dst;  /* source and dest address */
};

#define IP_HEADER_LENGTH(ip)       (((ip)->ip_hl))
#define IP_VERSION(ip)        (((ip)->ip_v))

/* TCP header */
    typedef u_int tcp_seq;

    struct tcp_header {
        u_short th_sport;   /* source port */
        u_short th_dport;   /* destination port */
        tcp_seq th_seq;     /* sequence number */
        tcp_seq th_ack;     /* acknowledgement number */
        u_char th_offx2;    /* data offset, rsvd */
    #define TH_OFFLENGTH(th)  (((th)->th_offx2 & 0xf0) >> 4)
        u_char th_flags;
    #define TH_FIN 0x01
    #define TH_SYN 0x02
    #define TH_RST 0x04
    #define TH_PUSH 0x08
    #define TH_ACK 0x10
    #define TH_URG 0x20
    #define TH_ECE 0x40
    #define TH_CWR 0x80
    #define TH_FLAGS (TH_FIN|TH_SYN|TH_RST|TH_ACK|TH_URG|TH_ECE|TH_CWR)
        u_short th_win;     /* window */
        u_short th_sum;     /* checksum */
        u_short th_urp;     /* urgent pointer */
};


typedef struct ethernet_header ethernet_header_t;
typedef struct ip_header ip_header_t;
typedef struct tcp_header tcp_header_t;

#endif /* _INMN_PACKET_H_ */

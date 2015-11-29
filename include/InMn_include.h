


#ifndef _INMN_INCLUDE_H_
#define _INMN_INCLUDE_H_


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>


/* Pcap Header Files */
#include <pcap.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "ifaddrs.h"
#include "sys/types.h"
#include "net/if.h"

/* Local Header Files */
#include "InMn_util.h"

/* Macro values */
#define ERROR -1
#define EOK    0
#define TRUE   1
#define FALSE  0
#define bool  int

/* Help Menu */
#define HELP LOG("Option:") \
             LOG("       -h -> help") \
             LOG("       -p -> Run in Process Model") \
             LOG("       -t -> Run in Thread Model") \
             LOG("       -n -> Name of Specifc Interface Eg: -n eth0 ")


/* For Printing */
#define LOG(a) printf(a"\n");



/*
 * Following is Structure of ifaddrs, Interface address retreived from 
 * getifaddrs()
 *
 *       struct ifaddrs {
 *             struct ifaddrs  *ifa_next;    // Next item in list 
 *             char            *ifa_name;    // Name of interface 
 *             unsigned int     ifa_flags;   // Flags from SIOCGIFFLAGS 
 *             struct sockaddr *ifa_addr;    // Address of interface 
 *             struct sockaddr *ifa_netmask; // Netmask of interface 
 *             union {
 *                 struct sockaddr *ifu_broadaddr;  // Broadcast address of interface 
 *                 struct sockaddr *ifu_dstaddr;    //  Point-to-point destination address 
 *             } ifa_ifu;
 *         #define              ifa_broadaddr ifa_ifu.ifu_broadaddr
 *         #define              ifa_dstaddr   ifa_ifu.ifu_dstaddr
 *             void            *ifa_data;   //  Address-specific data 
 *         };
 *
 */


typedef struct ifaddrs       ifaddrs_t;
typedef struct InMn_if_info_ InMn_if_info_t;
typedef struct InMn_stats_   InMn_stats_t;

struct InMn_stats_ {
    int         Packet_count;
};

struct InMn_if_info_ {
    ifaddrs_t          *InMn_if_addrs;
    InMn_stats_t        InMn_stats;
    FILE               *fp;
    InMn_if_info_t     *next;
};

/* Global Meter to maintain information regarding 
 * Interfaces ands Stats
 */
InMn_if_info_t  *InMn_if_info;


/*
 * Interfaces_count: To Maintain No Of Total Interfaces 
 * on NIC
 */
int Interfaces_count;


void InMn_get_output_options(char*);

#endif /* _INMN_INCLUDE_H_ */

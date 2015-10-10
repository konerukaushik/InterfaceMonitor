/*
 * File: InMn_pcap.h
 * author: Kaushik , Koneru
 * Email: konerukaushik@gmail.com
 *
 * In this File we maintain PCAP API's being abstracted
 * declarations
 */


#ifndef _INMN_PCAP_H_
#define _INMN_PCAP_H_

#include <pcap.h> /* if this gives you an error try pcap/pcap.h */
#include <InMn_include.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/if_ether.h> /* includes net/ethernet.h */
#include <netinet/ether.h>
#include <InMn_packet.h>



/* open the device for sniffing.

   pcap_t *pcap_open_live(char *device,int snaplen, int prmisc,int to_ms,
   char *ebuf)

   snaplen - maximum size of packets to capture in bytes
   promisc - set card in promiscuous mode?
   to_ms   - time to wait for packets in miliseconds before read
   times out
   errbuf  - if something happens, place error string here

 we call pcap_open_live (device, BUFSIZE, PRMISC, TOMS, errbuf);
 */

#define BUFSIZE  9120 /* Maximum Packet size to capture */

#define PRMISC  1 /* Promiscous Mode */

#define TOMS  -1 


void InMn_pcap_monitor(InMn_if_info_t *interface_info);


#endif /* ifndef _INMN_PCAP_H_ */

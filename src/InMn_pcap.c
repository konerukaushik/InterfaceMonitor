/*
 * File: InMn_pcap.c
 *
 * Author: Kaushik, Koneru
 *
 * Email: konerukaushik@gmail.com
 *
 */

#include <InMn_pcap.h>


/*
 * Function:InMn_monitor_interface
 * 		This function is the callback function for
 *              pcap_loop
 *       
 *  struct pcap_pkthdr {
 *      struct timeval ts;   time stamp 
 *      bpf_u_int32 caplen;  length of portion present 
 *      bpf_u_int32;         lebgth this packet (off wire) 
 *      }
 */

void
InMn_monitor_interface (u_char *argv, struct pcap_pkthdr *packethdr,
                          u_char *packet)
{
    const ethernet_header_t  *ether_hdr;
    const ip_header_t        *ip_hdr;
    const tcp_header_t       *tcp_hdr;
    u_int                     ip_hdr_len;
    u_int                     tcp_hdr_len;
    FILE                      *fp = (FILE *)argv;

    ether_hdr   = (ethernet_header_t *) packet;
    ip_hdr      = (ip_header_t *) packet + ETHERNET_HEADER_SIZE;
    ip_hdr_len  = IP_HEADER_LENGTH(ip_hdr) * 4;

    tcp_hdr     = (tcp_header_t *) packet + ETHERNET_HEADER_SIZE + ip_hdr_len;

    tcp_hdr_len = TH_OFFLENGTH(tcp_hdr);

    fprintf(stdout,"ethernet header source: %s\n",ether_ntoa((const struct ether_addr *)&ether_hdr->ether_shost));
    fprintf(fp,"ethernet header source: %s\n",ether_ntoa((const struct ether_addr *)&ether_hdr->ether_shost));
    fprintf(fp,"Got a Packet IP Length: %d, TCP Length: %d, ether_hdr type : %d\n", ip_hdr_len, tcp_hdr_len, ether_hdr->ether_type);
    fprintf(stdout,"Got a Packet IP Length: %d, TCP Length: %d, ether_hdr type : %d\n", ip_hdr_len, tcp_hdr_len, ether_hdr->ether_type);
    fprintf(fp,"Ethernet header  Destination Host Mac %c:%c:%c:%c:%c:%c\n", ether_hdr->ether_dhost[0], ether_hdr->ether_dhost[1], ether_hdr->ether_dhost[2],ether_hdr->ether_dhost[3],ether_hdr->ether_dhost[4],ether_hdr->ether_dhost[5]);
    fprintf(stdout,"Ethernet header  Destination Host Mac %c:%c:%c:%c:%c:%c\n", ether_hdr->ether_dhost[0], ether_hdr->ether_dhost[1], ether_hdr->ether_dhost[2],ether_hdr->ether_dhost[3],ether_hdr->ether_dhost[4],ether_hdr->ether_dhost[5]);
}

void
InMn_pcap_monitor (InMn_if_info_t  *interface_info) 
{

    pcap_t             *descrp;
    char                errbuf[PCAP_ERRBUF_SIZE];
    char               *interface_name;

    interface_name  = interface_info->InMn_if_addrs->ifa_name;

    descrp = pcap_open_live(interface_name, BUFSIZE, PRMISC, TOMS, errbuf);

    if (descrp == NULL) {
        printf("Unable to open FD on interface %s, err %s\n", interface_name, errbuf);
        exit(1);
    }

    interface_info->fp = fopen(interface_name,"w+");
    while(1)
    pcap_loop(descrp, 1,  (pcap_handler)InMn_monitor_interface, (u_char *)interface_info->fp);

    fclose(interface_info->fp);
    return;
}

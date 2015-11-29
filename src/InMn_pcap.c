/*
 * File: InMn_pcap.c
 *
 * Author: Kaushik, Koneru
 *
 * Email: konerukaushik@gmail.com
 *
 */

#include <InMn_pcap.h>
#include <InMn_filter.h>
#include <InMn_include.h>

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
    const ethernet_header_t   *ether_hdr;
    const ip_header_t         *ip_hdr;
    InMn_if_info_t            *InMn_if = (InMn_if_info_t *)argv;
    FILE                      *fp = InMn_if->fp;
    char                       srcip[256], dstip[256];
    char		       srcmac[256], dstmac[256];
    char                      *name;
    /* New */
    char *server = "127.0.0.1"; 
    struct sockaddr_in myaddr, remaddr;
    int fd, i = 0, slen=sizeof(remaddr);

    

    ether_hdr   = (ethernet_header_t *) packet;
    ip_hdr      = (ip_header_t *) (packet + ETHERNET_HEADER_SIZE) ;
    

    if (ip_hdr->ip_p == IPPROTO_IP) {
        /* Skip RAW IP Packets */
	return;
    }
	
    name = InMn_if->InMn_if_addrs->ifa_name;
    strcpy(srcip,  inet_ntoa(ip_hdr->ip_src));
    strcpy(dstip,  inet_ntoa(ip_hdr->ip_dst));
    strcpy(srcmac, ether_ntoa((struct ether_addr *)&ether_hdr->ether_shost));
    strcpy(dstmac, ether_ntoa((struct ether_addr *)&ether_hdr->ether_dhost));


    fprintf(stdout, "%s   %s   %s   %s   %s\n",name, dstmac,srcmac, srcip, dstip); 
    fprintf(fp, "Interface%s   Ethernet Dest:%s    Ethernet Source: %s  Source IP: %s Dest IP:%s\n",name, dstmac,srcmac, srcip, dstip); 

    if (output_filter.output_netport && (output_filter.O_output_interface_descrp != NULL)) {
	    if (pcap_inject(output_filter.O_output_interface_descrp,packet,packethdr->len) == -1) {
		    pcap_perror(output_filter.O_output_interface_descrp, 0);
	    }
    }

    /* Check for local port output configuration */

    if (output_filter.output_port && (output_filter.O_port_num)) {

	    if ((fd=socket(AF_INET, SOCK_DGRAM, 0))==-1)
		    printf("socket created\n");

	    /* bind it to all local addresses and pick any port number */

	    memset((char *)&myaddr, 0, sizeof(myaddr));
	    myaddr.sin_family = AF_INET;
	    myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	    myaddr.sin_port = htons(0);

	    if (bind(fd, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0) {
		    perror("bind failed");
		    return;
	    }

	    /* now define remaddr, the address to whom we want to send messages */
	    /* For convenience, the host address is expressed as a numeric IP address */
	    /* that we will convert to a binary format via inet_aton */

	    memset((char *) &remaddr, 0, sizeof(remaddr));
	    remaddr.sin_family = AF_INET;
	    remaddr.sin_port = htons(output_filter.O_port_num);
	    if (inet_aton(server, &remaddr.sin_addr)==0) {
		    fprintf(stderr, "inet_aton() failed\n");
		    exit(1);
	    }

	    /* now let's send the messages */

	    printf("Sending packet %d to %s port %d\n", i, server, output_filter.O_port_num);
	    if (sendto(fd, packet, packethdr->len, 0, (struct sockaddr *)&remaddr, slen)==-1)
		    perror("sendto");

	    close(fd);

    }

    return;
}

void
InMn_pcap_monitor (InMn_if_info_t  *interface_info) 
{

    pcap_t               *descrp;
    char                  errbuf[PCAP_ERRBUF_SIZE];
    char                 *interface_name;
    struct bpf_program    bpfpr;		/* The compiled filter */

    interface_name  = interface_info->InMn_if_addrs->ifa_name;

    descrp = pcap_open_live(interface_name, BUFSIZE, PRMISC, TOMS, errbuf);

    if (descrp == NULL) {
        printf("Unable to open FD on interface %s, err %s\n", interface_name, errbuf);
        exit(1);
    }

    
    if (input_filter) {
	printf("Applying Filter %s \n", filter_options);
	if (pcap_compile(descrp, &bpfpr, filter_options ,0, PCAP_NETMASK_UNKNOWN) == -1) {
	fprintf(stderr, "Couldn't parse filter %s: %s\n", filter_options, pcap_geterr(descrp));
	exit(1);
	}
	
	if (pcap_setfilter(descrp, &bpfpr) == -1) {
		fprintf(stderr, "Couldn't install filter %s: %s\n", filter_options, pcap_geterr(descrp));
		exit(1);
	}	
    }
   
    if (output_filter.output_netport) {

	if (output_filter.O_output_interface != NULL) {
		if (strncmp(output_filter.O_output_interface, interface_name, strlen(interface_name))) {
			output_filter.O_output_interface_descrp = descrp;
		}
	}
    }
    interface_info->fp = fopen(interface_name,"w+");

    while(1) {
	    pcap_loop(descrp, 1,  (pcap_handler)InMn_monitor_interface, (u_char *)interface_info);
    }

    fclose(interface_info->fp);
    return;
}

/*
 *
 * Author: Kaushik, Koneru
 *
 * Email: konerukaushik@gmail.com
 *
 * In this file we maintain DB details of the Packet Information
 */

#ifndef _INMN_FILTER_
#define _INMN_FILTER_

/* Using this Structure we need to create a String 
 * and set the filter on each file descriptor
 * created on the interfaces
 */
struct _InMn_filter_output_ {
    /* Output Options */
    int                  output_netport;
    char                *O_output_interface;
    pcap_t              *O_output_interface_descrp;
    int                  O_port_num;
    int                  output_port;

};

typedef struct _InMn_filter_output_ _InMn_filter_output_t;


extern _InMn_filter_output_t output_filter;
extern bool input_filter;;
extern char *filter_options;

#endif /* __INMN_FILTER__ */

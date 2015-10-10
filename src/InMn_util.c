/*
 * File: InMn_util.c
 * Author: Koneru, Kaushik
 * Email: konerukaushik@gmail.com
 *
 * This File is to Maintain all the necessary 
 * Utilities Function like accessing any information from
 * OS, BookKeeping
 */

#include "InMn_include.h"


InMn_if_info_t * 
InMn_alloc_mem_struct ()
{
    InMn_if_info_t      *temp;

    temp = (InMn_if_info_t *) malloc(sizeof(InMn_if_info_t));

    if (temp == NULL) {
        LOG("Unable to Allocate Memory")
        return NULL;
    }

    /* Initialize the varaibles */
    temp->InMn_if_addrs = NULL;
    temp->InMn_stats.Packet_count = 0;
    temp->next = NULL;
    
    return temp;
}


/*
 *
 *  Create a Interface node and assign to Global
 */
InMn_if_info_t *
InMn_add_interfaces_info (ifaddrs_t *interface_info) 
{
    InMn_if_info_t         *InMn_temp = NULL;

    InMn_temp = InMn_alloc_mem_struct();

    if (InMn_temp == NULL) {
        printf("Unable to Allocate memory for Interface");
        return NULL;
    }

    InMn_temp->InMn_if_addrs = interface_info;

    return InMn_temp;

}

/* 
 * Function: InMn_retreive_interfaces
 *          This function is used to retrieve OS network Interfaces
 */
int 
InMn_retrieve_interfaces ()
{

    ifaddrs_t         *Interfaces_addrs, *temp;
    InMn_if_info_t    *InMn_temp                 = NULL;

    Interfaces_count = 0; 

    InMn_if_info = InMn_temp;

    /* Get Interfaces List */
    getifaddrs(&Interfaces_addrs);

    temp = Interfaces_addrs;

    while (temp) {
        if ((!(temp->ifa_addr)) || (!(temp->ifa_flags & IFF_RUNNING)) || (temp->ifa_flags & IFF_LOOPBACK) ||
                 !(temp->ifa_addr->sa_family == AF_PACKET)) {
            temp = temp->ifa_next;
            continue;
        }

        if (InMn_if_info == NULL ) {
            InMn_if_info = InMn_add_interfaces_info(temp);
            InMn_temp = InMn_if_info;
            Interfaces_count++;
            temp = temp->ifa_next;
            continue;
        }

        InMn_temp = InMn_if_info;

        while (InMn_temp->next != NULL) {
            InMn_temp = InMn_temp->next;
        }

        InMn_temp->next = InMn_add_interfaces_info(temp);

        temp = temp->ifa_next;

        Interfaces_count++;
    }

    freeifaddrs(Interfaces_addrs);
    freeifaddrs(temp);

    return EOK;
    
}

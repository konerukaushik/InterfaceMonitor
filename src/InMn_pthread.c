/*
 * File: InMn_thread.c
 * Author: Koneru, Kaushik
 * Email: konerukaushik@gmail.com
 *
 * This File contains method to launch threads for each thread
 */

#include <InMn_pthread.h>

/*
 * Function: InMn_thread_info_mem_alloc
 *          In this function we allocate Memory for 
 *          InMn_thread_info
 */
thread_info_t*
InMn_thread_info_mem_alloc()
{
    thread_info_t           *temp;

    temp = (thread_info_t *) malloc (sizeof(thread_info_t));

    if (temp == NULL) {
        return NULL;
    }

    /* Nullify the variables */
    temp->thread_id = 0;
    temp->thread_num = 0;
    temp->argv = NULL;
    temp->next =NULL;
    return temp;
}


/* 
 * Function: InMn_thread_init
 * This Function is the callback function for thread init
 * In this function we open a pcap for registered interfaces
 */
static void *
InMn_thread_init(void *InMn_thread_args)
{

    thread_info_t       *thread_info                 = InMn_thread_args;
    InMn_if_info_t      *interface_info              = NULL;
    
    
    interface_info = thread_info->argv; 

    printf("Received Interface Information :%s\n", interface_info->InMn_if_addrs->ifa_name);

    InMn_pcap_monitor(interface_info);

    return thread_info;
}

/*
 * Function: InMn_monitor_interfaces_thread
 * In This function we trigger the Threads to Monitor Interfaces
 */
int 
InMn_monitor_interfaces_thread()
{

    pthread_attr_t          attr;
    int                     stack_size               = 0x100000; /* Allocate 1MB to each Thread */
    int                     iteration                = 0 ;
    static int              initialize               = 0 ;
    thread_info_t          *InMn_thread_temp         = NULL;
    thread_info_t          *InMn_thread_temp_parse   = NULL;
    InMn_if_info_t         *InMn_if_temp             = NULL;
    int                     ret = 0;
    void                   *res;


    /* Assign Thread Information */
    InMn_thread_temp = InMn_thread_info;
    InMn_if_temp = InMn_if_info;

    /* Create a Common template of Thread Properties */
    
    /*Initialize thread Attributes */
    ret = pthread_attr_init(&attr);
    if (ret != 0) {
        LOG("Unable to create a Thread Attributes");
        return ERROR;
    }

    /* Setting Stack size for ptheard to 1 MB */
    ret = pthread_attr_setstacksize(&attr, stack_size);
    if (ret != 0) {
        LOG("Unable to set Stack Size for the thread Attr Properties ");
        return ERROR;
    }

    for (iteration = 0; iteration < Interfaces_count; iteration++) {

        /* Allocate Memory for Each Thread For Book Keeping */
        if (InMn_thread_temp_parse == NULL) {
            InMn_thread_temp_parse = InMn_thread_info_mem_alloc();
            if (InMn_thread_temp_parse == NULL) {
                LOG("Unable to Allocate Memory for Thread");
                return ERROR;
            }

            if (!initialize) {
                /* Initialize the Variables */
                InMn_thread_temp = InMn_thread_temp_parse;
                InMn_thread_info = InMn_thread_temp;
                initialize++;
            } else {
                InMn_thread_temp->next = InMn_thread_temp_parse;
                InMn_thread_temp = InMn_thread_temp->next;
            }
        }

        /* Create Thread By Filling Local Data Structure */

        /* Fill Local Interface Information */
        if ( &(InMn_if_info[iteration]) != NULL) {
            InMn_thread_temp_parse->argv = InMn_if_temp; 
        } else {
            printf("Iteration %d is having a NULL interface \n",iteration);
            return ERROR;
        }

        /* Fill Thread Number */
        InMn_thread_temp_parse->thread_num = iteration + 1 ;

        /* Create Thread */
        ret = pthread_create(&(InMn_thread_temp_parse->thread_id), &attr,
                             &InMn_thread_init, (InMn_thread_temp_parse));
                            
        InMn_thread_temp_parse = InMn_thread_temp_parse->next;
        InMn_if_temp = InMn_if_temp->next;

    }

    ret = pthread_attr_destroy(&attr);

    if (ret != 0 ) {
        LOG("Unable to Destroy attr");
        return 0;
    }

    InMn_thread_temp = InMn_thread_info;

    for (iteration = 0; iteration < Interfaces_count; iteration++) {
        pthread_join(InMn_thread_temp->thread_id, &res);
        InMn_thread_temp = InMn_thread_temp->next;
    }
    return EOK;

}

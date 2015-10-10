/*
 *
 * File: InMn_pthread.h
 * Author: Koneru, Kaushik
 * Email: konerukaushik@gmail.com
 *
 * This file is to maintain pthread information of the Process
 */

#ifndef _INMN_PTHREAD_H_
#define _INMN_PTHREAD_H_

#include <pthread.h>
#include <InMn_include.h>
#include <InMn_pcap.h>

typedef struct thread_info_ thread_info_t;

struct thread_info_ {

    pthread_t        thread_id;
    int              thread_num;      /* Application thread number */
    InMn_if_info_t  *argv;            /* Thread Infomation */
    thread_info_t   *next;
};

thread_info_t  *InMn_thread_info;

int InMn_monitor_interfaces_thread();

thread_info_t * InMn_thread_info_mem_alloc();


#endif  /* _INMN_PTHREAD_H_ */

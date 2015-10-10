#include "InMn_include.h"
#include "InMn_pthread.h"

/*
 *
 * Method 
 *
 * 1.) Option
 * 2.) Thread and Process
 * 3.) Capture Packets from Interface
 * 4.) Option to Either Capture to TextFile or Hash and Print Stats
 */

int main (int argc, char **argv)
{
    int             process_flag        = 0; /* Run in Process */
    int             thread_flag         = 0; /* Run in Thread */
    int             interface_specified = 0; /* If User Specified Interface */
    int             c;
    char           *Interface_name;
    int             Option_size  = 0;


    if (argc <= 1 ) {
        HELP;
        return ERROR;
    }
     while ( (c = getopt(argc, argv, "pthn:")) != ERROR ) {
         switch (c) {
            case 'p':
                if (!thread_flag) {
                    LOG("Running in Process Model");
                    process_flag = 1;
                } else {
                    LOG(" Previously Triggered in Thread Model");
                }
                break;
            case 't':
                if (!process_flag) {
                    LOG("Running in Thread Model");
                    thread_flag = 1;
                } else {
                    LOG(" Previously Triggered in Process Model");
                }
                break;
            case 'n':
                Option_size = sizeof(optarg) * sizeof(char);
                Interface_name = (char *) malloc(Option_size);
                memmove(Interface_name, optarg, Option_size);
                printf("Interface Selected --> %s, OptArg --> %s \n", Interface_name, optarg);
                interface_specified = 1;
                break;
            case 'h':
            default:
                HELP;
                return ERROR;
        }
     }

     /* Initially Find Out number of interfaces bookstore them */
    
     /* If Interface is not Specified by User, Then Book Keep All the Existing Network Interfaces */
     if (!interface_specified) {
         InMn_retrieve_interfaces();
     }


     if (process_flag) {
      //  InMn_monitor_interfaces_process();
     } else {
        InMn_monitor_interfaces_thread();
     }

    return EOK;
}

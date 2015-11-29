#include <InMn_include.h>
#include <InMn_pthread.h>
#include <InMn_filter.h>


/*declarations 
 *
 */

_InMn_filter_output_t output_filter = { .O_output_interface_descrp = NULL, .output_netport = FALSE, .output_port = FALSE };

bool input_filter = FALSE;

char *filter_options;

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


    if (argc <= 1 ) {
        HELP;
        return ERROR;
    }
     while ( (c = getopt(argc, argv, "pths:n:o:")) != ERROR ) {
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
		Interface_name = optarg;
                printf("Interface Selected --> %s, OptArg --> %s \n", Interface_name, optarg);
                interface_specified = 1;
                break;
	    case 's':
		filter_options = optarg;
		printf(" Filter Options -->%s, OptArg --> %s \n",filter_options, optarg);
		input_filter = TRUE;
		break;
            case 'o':
                /* Output Options, As of now 
                 * 1 --> netport eth0
                 * 2 --> port 2200
                 */
		printf(" Output Options --> %s \n",  optarg);
		InMn_get_output_options(optarg);
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
      /* TBD, To run this Process in Multi-Process Model */
      //  InMn_monitor_interfaces_process();
     } else {
        InMn_monitor_interfaces_thread();
     }

    return EOK;
}


void 
InMn_get_output_options( char *output_options) {
	char		*required_output;
	int		 output_length;

	output_length = strlen(output_options);

	if (strstr(output_options, "net") != NULL) {
		printf("Received netport output\n");
		required_output = strndup(output_options+8, output_length-8);
		output_filter.output_netport = TRUE;
		output_filter.O_output_interface = required_output;
	} else if (strstr(output_options, "port") != NULL){
		printf("Received local port output \n");
                required_output = strndup(output_options+5 , output_length-5);
		output_filter.output_port = TRUE;
		output_filter.O_port_num = atoi(required_output);		
	} else if ( strstr(output_options, "file") != NULL) {
		
	} else {
		printf("Received unvalid input for Output interface\n");
		abort();
	}	

	printf("%d\n%s\n%d\n%d\n", output_filter.output_netport, output_filter.O_output_interface, output_filter.output_port, output_filter.O_port_num);
	
}

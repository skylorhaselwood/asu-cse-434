// William Skylor Haselwood
// Nathaniel Flick
// Arizona State University - CSE 434 Computer Networks — Fall 2014
// Instructor: Dr. Violet R. Syrotiuk
// Two-Person Team Socket Programming Project

#include <stdio.h>                  /* for printf() and fprintf() */
#include <sys/socket.h>             /* for socket(), connect(), sendto(), and recvfrom() */
#include <arpa/inet.h>              /* for sockaddr_in and inet_addr() */
#include <stdlib.h>                 /* for atoi() and exit() */
#include <string.h>                 /* for memset() */
#include <unistd.h>                 /* for close() */
#include </home/Skylor/client.h>    /* for client structures */
#include </home/Skylor/request.h>   /* for request structures */
#include <sys/time.h>               /* for timeout */

#define FileLockMAX 255             /* Longest string to FileLock */


int main(int argc, char **argv) 
{

    int respStringLen;                      /* Length of received response */
    char FileLockBuffer[FileLockMAX+1];     /* Buffer for receiving FileLocked string */


    // Tests for correct number of arguments
    if (argc != 6) 
    {
        fprintf(stderr, "usage: %s <SERVER IP> <MACHINE NAME> <CLIENT ID> <SERVER PORT> <SCRIPT FILE>\n", argv[0]);
        exit(1);
    }

    // Initializes socket
    int sock;
    if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
        fail_with_error("socket() failed");

    // Constructs the server address
    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr(argv[1]);
    server_address.sin_port = htons(atoi(argv[4]));


    // Request initializer
    request_t request;
    strcpy(request.machine, argv[2]);
    strcpy(request.operation, argv[5]);
    request.client = atoi(argv[3]);
    request.request = atoi(argv[6]);


    // Timeout structure for server response
    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 100000;


    // Initialize script and incarnation file
    FILE *Script;
    FILE *incarnationFile;

    // Open script
    Script = fopen(argv[5],"r");
    incarnationFile = fopen('/home/Skylor/incarnationFile.txt',"rw");

    // Initialize variables to be stored from script
    char    command;    // Script command
    char    filename;   // Filename associated with script command
    char    mode;       // Mode of the open operation
    int     bytes;      // Number of bytes associated with certain script commands
    char    string;     // String associated with certain script command
    char    operation;  // Full operation code sent to the server including command and arguments
    int     requestNumber = 0; // Updated to count the number of requests sent to the server




   
   
   // Reads script file to send commands to the server
    for (command = getc(Script); command != EOF; command = getc(Script))
    {
        if (command == "open")  // Open command
        {

            // Searches and stores the filename and mode variables
            filename = getc(Script);
            mode = getc(Script);


            // Creates a string that holds the message to be sent to the server
            operation = command + " " + filename + " " + mode;

            // Creates a request
            request_t request;
            strcpy(request.machine, argv[2]);
            strcpy(request.operation, operation);
            request.client = atoi(argv[3]);
            request.request = atoi(requestNumber);

            // Sends the request and tuple to the server
            if (sendto(sock, &request, sizeof(request_t), 0, (struct sockaddr *)
               &server_address, sizeof(server_address)) != sizeof(request_t))
            fail_with_error("sendto() sent a different number of bytes than expected");

            // Increments the request number
            requestNumber = requestNumber + 1;

        }

        if (command == "close") // Close command
        {

            // Searches and stores the filename and mode variables
            filename = getc(Script);

            // Creates a string that holds the message to be sent to the server
            operation = command + " " + filename;

            // Creates a request
            request_t request;
            strcpy(request.machine, argv[2]);
            strcpy(request.operation, operation);
            request.client = atoi(argv[3]);
            request.request = atoi(requestNumber);

            // Sends the request and tuple to the server
            if (sendto(sock, &request, sizeof(request_t), 0, (struct sockaddr *)
               &server_address, sizeof(server_address)) != sizeof(request_t))
            fail_with_error("sendto() sent a different number of bytes than expected");

            // Increments the request number
            requestNumber = requestNumber + 1;        

        }

        if (command == "read")  // Read command
        {
           
            // Searches and stores the filename and mode variables
            filename = getc(Script);
            bytes = getw(Script);


            // Creates a string that holds the message to be sent to the server
            operation = command + " " + filename + " " + bytes;

            // Creates a request
            request_t request;
            strcpy(request.machine, argv[2]);
            strcpy(request.operation, operation);
            request.client = atoi(argv[3]);
            request.request = atoi(requestNumber);

            // Sends the request and tuple to the server
            if (sendto(sock, &request, sizeof(request_t), 0, (struct sockaddr *)
               &server_address, sizeof(server_address)) != sizeof(request_t))
            fail_with_error("sendto() sent a different number of bytes than expected");

            // Increments the request number
            requestNumber = requestNumber + 1;

        }

        if (command == "write") // Write command
        {
            
            // Searches and stores the filename and mode variables
            filename = getc(Script);
            string = getc(Script);


            // Creates a string that holds the message to be sent to the server
            operation = command + " " + filename + " " + string;

            // Creates a request
            request_t request;
            strcpy(request.machine, argv[2]);
            strcpy(request.operation, operation);
            request.client = atoi(argv[3]);
            request.request = atoi(requestNumber);

            // Sends the request and tuple to the server
            if (sendto(sock, &request, sizeof(request_t), 0, (struct sockaddr *)
               &server_address, sizeof(server_address)) != sizeof(request_t))
            fail_with_error("sendto() sent a different number of bytes than expected");

            // Increments the request number
            requestNumber = requestNumber + 1;

        }

        if (command == "lseek") // Lseek command
        {
            
            // Searches and stores the filename and mode variables
            filename = getc(Script);
            bytes = getc(Script);


            // Creates a string that holds the message to be sent to the server
            operation = command + " " + filename + " " + bytes;

            // Creates a request
            request_t request;
            strcpy(request.machine, argv[2]);
            strcpy(request.operation, operation);
            request.client = atoi(argv[3]);
            request.request = atoi(requestNumber);

            // Sends the request and tuple to the server
            if (sendto(sock, &request, sizeof(request_t), 0, (struct sockaddr *)
               &server_address, sizeof(server_address)) != sizeof(request_t))
            fail_with_error("sendto() sent a different number of bytes than expected");

            // Increments the request number
            requestNumber = requestNumber + 1;

        }

        else    // Fail command
        {
            int fail = 1;
            fprintf(incarnationNumber,"%d",fail);
        }
        // End of command cases





    // Prints out the operation sent to the server read from the script file
    printf("Operation Processed: %d\n",operation);


    // Recieves a response from the server
    fromSize = sizeof(server_address);
    if ((respStringLen = recvfrom(sock, FileLockBuffer, FileLockMAX, 0, 
         (struct sockaddr *) &server_address, &fromSize)) != FileLockStringLen)
        DieWithError("recvfrom() failed");

    // Null-terminates the received data
    FileLockBuffer[respStringLen] = '\0';
    printf("Received: %s\n", FileLockBuffer);    /* Print the FileLocked arg */



    // Time out for server response
    else if (setsockopt(rcv_sock, SOL_SOCKET, SO_RCVTIMEO,&tv,sizeof(tv)) < 0)
            { 
                perror("Error: Server response timed Out..");
            }

    } // End of client commands sent to server



    
    close(sock);
    fclose(Script);
    fclose(incarnationFile);
    exit(0);

} // End of program





// External error handeling function
void fail_with_error(const char* msg)
{
    perror(msg);
    exit(1);
}

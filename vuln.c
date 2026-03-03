#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h> 


#include "client_cli.h"
// Constants
const char* HELP_MESSAGE ="[i] Available commands:\n  - HELP\n  - TIME\n  - SAVE\n  - INFO\n  - ECHO\n  - EXIT\n";
const int RESPONSE_SIZE = 1028;
//


char* printresponse(char *str, int info){
    char buffer[60];
    if(info){
        return &buffer;
    }
    strcpy(buffer,str);
}

int main(int argc, char *argv[])
{

    int port;
    if( argc == 2){
        port = atoi(argv[1]);
    } else {
        port = 9999;
    }
    int listenfd = 0, client = 0;
    struct sockaddr_in serv_addr; 

    char sendBuff[RESPONSE_SIZE];
    time_t ticks; 
    char client_message[2000];
    memset(client_message, 0, sizeof(client));

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sendBuff, '0', sizeof(sendBuff)); 

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(port); 

    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); 

    listen(listenfd, 10); 
    printf("Started serveur on localhost at port : %d\n",port);
    puts("Waiting for incoming connections...");

    while(1)
    {
        client = accept(listenfd, (struct sockaddr*)NULL, NULL); 
        write(client , "[i] Welcome! Type HELP for commands.\n" , 37);
        client_input(client);
        int file_number = 0;

        while( (recv(client , client_message , 2000 , 0)) > 0 )
            {
                if (strncmp(client_message, "HELP", 4) == 0){
                        write(client, HELP_MESSAGE, strlen(HELP_MESSAGE)); 
                        client_input(client);
                }
                else if (strncmp(client_message, "TIME", 4) == 0){
                    
                    printresponse(client_message,1);
                    //Send the message back to client
                    ticks = time(NULL);
                    snprintf(sendBuff, sizeof(sendBuff), "%.24s\r\n", ctime(&ticks));
                    epilogue(client,sendBuff);
                }

                else if (strncmp(client_message, "INFO", 4) == 0){
                    char *printresponse_ptr = printresponse("",0);
                    snprintf(sendBuff, sizeof(sendBuff), "[i] INFO:\n %s : %p\n","buffer", &printresponse_ptr);
                    epilogue(client,sendBuff);
                }

                else if (strncmp(client_message, "ECHO", 4) ==0){
                    // We send back the client message 
                    snprintf(sendBuff, sizeof(sendBuff),client_message);
                    epilogue(client,sendBuff);
                }

                else if (strncmp(client_message, "SAVE", 4) ==0){
                    char *to_save = &client_message[4];
                    char cmd[RESPONSE_SIZE];
                    // Creating the command to save the payload
                    snprintf(cmd,sizeof(cmd), "echo \"%s\" > %d_client_%d_save.txt",to_save,file_number++,client);
                    // Executing the command
                    int code = system(cmd);
                    // Notification to client
                    snprintf(sendBuff, sizeof(sendBuff),"Save on server : %s\nReturn code %d\n", to_save, code);
                    epilogue(client,sendBuff);
                }



                else if (strncmp(client_message, "EXIT", 4) == 0){
                        write(client, "[i] Bye\n", 8); 
                        close(client);
                }
                
                else{
                    write(client, HELP_MESSAGE, strlen(HELP_MESSAGE)); 
                    client_input(client);
                }
                // We erase everything from the precedent message
                memset(sendBuff, 0, sizeof(sendBuff));
                memset(client_message, 0, sizeof(client_message));
            }
   
    }
}

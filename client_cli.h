#ifndef H_CLIENT_CLI
#define H_CLIENT_CLI
#include <string.h>
#include <stdio.h>
#include <unistd.h>

// Client helper
void client_input(int client){
    char buf[10];
    snprintf(buf,sizeof(buf),"%d : ",client);
    write(client, "client ",8);
    write(client,buf,strlen(buf));
}
void epilogue(int client, char* to_send){
    write(client, to_send, strlen(to_send)); 
    client_input(client);
}
// ----------------





#endif
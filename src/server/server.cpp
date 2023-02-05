#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#define PORT "3000"

int main(int argc,char **argv){

struct addrinfo hint,*res,*p;
memset(&hint,0,sizeof hint); //Important, else produces bad value for ai flag
int yes = 1;
int sockfd;
hint.ai_family = AF_UNSPEC;
hint.ai_protocol = SOCK_STREAM;
hint.ai_flags = AI_PASSIVE;  //set server IP

int rv = getaddrinfo(NULL,PORT,&hint,&res);
if(rv == -1){
    fprintf(stderr,"1. %s \n",gai_strerror(rv));
    exit(1);
}
p = res;
sockfd = socket(p->ai_family,p->ai_socktype,p->ai_protocol);
if(sockfd == -1){
    fprintf(stderr,"2. %s \n",gai_strerror(sockfd));
    exit(1);
}

if(setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof yes)==-1){
   perror("3.Error in setsockopt");
   exit(1);
}

if(bind(sockfd,p->ai_addr,p->ai_addrlen)==-1){
   perror("4.Error in binding");
   exit(1); 
}

return 0;

}






















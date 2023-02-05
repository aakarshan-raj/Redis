#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#define BACKLOG 10


static void do_something(int fd){
    //read first 
    char rbuf[64] = {};
    ssize_t n = read(fd,rbuf,sizeof(rbuf)-1);
    if(n<0){
        perror("Error reading");
        exit(1);
    }
    printf("Client say %s\n",rbuf);

    char wbuf[] = "World";

    int w = write(fd,wbuf,strlen(wbuf));
  if(w<0){
        perror("No one can listen to you :(");
        exit(1);
    }
    //the write
}
void *get_in_addr(struct sockaddr *sa){
   if(sa->sa_family == AF_INET){
   return &(((struct sockaddr_in*)sa)->sin_addr); 
   }
   return &(((struct sockaddr_in6*)sa)->sin6_addr);
}



int main(int argc,char **argv){

if(argc < 2){
    printf("Provide : [PORT]\n");
    exit(1);
}

struct addrinfo hint,*res,*p;
memset(&hint,0,sizeof hint); //Important, else produces bad value for ai flag
int yes = 1;
int sockfd;
hint.ai_family = AF_UNSPEC;
hint.ai_socktype = SOCK_STREAM;
hint.ai_flags = AI_PASSIVE;  //set server IP

int rv = getaddrinfo(NULL,argv[1],&hint,&res);
if(rv == -1){
    fprintf(stderr,"1. ons for the actu%s \n",gai_strerror(rv));
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

if(listen(sockfd,BACKLOG) == -1){
   perror("5.listening");
   exit(1);
}
char addl[100];
while(true){
    struct sockaddr_storage client_addr;
    socklen_t client_size = sizeof client_addr;
    int accept_fd = accept(sockfd,(struct sockaddr*)&client_addr,&client_size);
    if(accept_fd < 0){
        perror("6.Accept");
        continue;
    }
    // inet_ntop(client_addr.ss_family,
    // get_in_addr(((struct sockaddr*)&client_addr))
    // ,addl,
    // sizeof addl);
    // printf("%s \n",addl);
    do_something(accept_fd);
    close(accept_fd);    
    
   

}

close(sockfd);
return 0;

}


























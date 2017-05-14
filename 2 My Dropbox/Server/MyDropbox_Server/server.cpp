#include "server.h"
#include "client.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <serverUtility.h>

#include <iostream>
using namespace std;

int main(int argc, char *argv[]){
    connectDatabase("database.db"); //arg[2]

    int sockfd,newsockfd;

    sockfd = createNewConnection("4001");

    newsockfd = acceptConnection(sockfd);

    Client* client = new Client(newsockfd);
    handleClient(client);
    close(sockfd);

    return 0;
}

int createNewConnection(char* portNumber){
    int sockfd, portno;
    struct sockaddr_in serv_addr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0){
        error("ERROR opening socket");
        exit(0);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = atoi(portNumber);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0){
        error("ERROR on binding");
        exit(0);
    }

    listen(sockfd,5);

    return sockfd;
}

int acceptConnection(int sockfd){
    int newsockfd;
    socklen_t clilen;
    struct sockaddr_in cli_addr;

    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
    if (newsockfd < 0){
      error("ERROR on accept");
    }

    return newsockfd;
}

void handleClient(Client* client){
    clientToServerMessage cmsg;
    int i=1;
    do{
        cout<<"i="<<i++<<endl;
        cmsg = client->recieveMessage();
        client->handleMessage(cmsg);
    }while(cmsg != LOGOUT);

    if (cmsg == LOGOUT) {
        //delete client;
        //Client* c = new Client(acceptNewConnection(sockfd));
        //handleClient(c);
    }
}

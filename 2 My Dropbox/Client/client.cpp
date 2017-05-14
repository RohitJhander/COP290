#include "client.h"
#include "clientUtility.h"
#include "commonUtility.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include <iostream>
using namespace std;

Client::Client(){

}

Client::Client(char* hostname, char *portnumber){
    connectToServer(hostname,portnumber);
}


void Client::connectToServer(char* hostname, char* portNumber){
    int portno;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    portno = atoi(portNumber);
    this->sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (this->sockfd < 0){
        error("ERROR opening socket");
        exit(0);
    }
    server = gethostbyname(hostname);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(this->sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0){
        error("ERROR connecting");
        exit(0);
    }
}

void Client::sendFileToServer(const char* fileName){
    fileData* data = readFromFile(fileName);
    sendFileDataToServer(data);
    delete data;
}

void Client::sendMessageToServer(clientToServerMessage msg){
    fileData* data = copyMessageToBuffer(msg);
    sendFileDataToServer(data);
    delete data;
}

void Client::sendFileDataToServer(fileData* data){
    cout<<"--------------Entering sendFileDataToServer()----------------"<<endl;
    cout<<"data->size: "<<data->size<<endl;
    int bytes_Sent = 0 ;
    int toSend;
    while(true){
        toSend = std::min(DEFAULT_PACKET_SIZE,data->size-bytes_Sent);
        int n = write(sockfd,(data->buffer)+bytes_Sent,toSend);
        cout<<"n = "<<n<<endl;
        if (n < 0){
            error("ERROR sending to socket");
        }else if(n == 0){
            cout<<"Finished sending to socket\n";
            break;
        }
        bytes_Sent += n;
    }
    cout<<"---------------Exiting sendFileDataToServer()-----------------"<<endl;
}

fileData* Client::recieveFileFromServer() {
    cout<<"------------------Entering recieveFileFromServer()----------------"<<endl;
    fileData* data = readFromServer(4);
    int sizeOfFile = getInt(data);
    delete data;
    data = readFromServer(sizeOfFile-4);
    cout<<"------------------Ending recieveFileFromServer()-----------------"<<endl;
    return data;
}

serverToClientMessage Client::recieveMessageFromServer(){
    fileData* data = readFromServer(4);
    serverToClientMessage msg;
    memcpy(&msg,data->buffer,sizeof(msg));

    return msg;
}

void Client::handleMessage(serverToClientMessage msg){
    switch(msg){
        case OK:
            cout<<"Ok\n";
            break;
        case NOT_OK:
            cout<<"Not Ok\n";
            break;
        default:
            break;
    }
}

bool Client::checkLogin(string username, string password) {
    fileData *f = writeLoginDetails(username, password);
    sendFileDataToServer(f);//sockfd should be made variable of class
    serverToClientMessage msg = recieveMessageFromServer();
    handleMessage(msg);
    if(msg==OK){
        return true;
    }
    return false;
}

bool Client::registerUser(string username, string password, string email) {
    fileData *f = writeRegisterDetails(username, password, email);
    sendFileDataToServer(f);//sockfd should be made variable of class
    serverToClientMessage msg = recieveMessageFromServer();
    if(msg==OK){
        return true;
    } else {
        return false;
    }
}

void Client::closeConnection() {

}

fileData* Client::readFromServer(int bytesToRead){
    fileData* data = new fileData();
    data->buffer = new char[bytesToRead];
    data->size = bytesToRead;

    int bytesRead = 0;
    while(bytesRead < bytesToRead){
        int n = read(sockfd,(data->buffer)+bytesRead,std::min(DEFAULT_PACKET_SIZE,bytesToRead-bytesRead));
        cout<<"n="<<n<<endl;
        if (n < 0){
            error("ERROR reading from socket");
        }else if(n == 0){
            cout<<"Finished reading from socket"<<endl;
            break;
        }
        bytesRead += n;
    }
    return data;
}

void Client::sendFileDetails(File* file){
    fileData* data = getFileDetails(file);
    sendFileDataToServer(data);
    delete data;
}

void Client::uploadFile(File* file){
    uploadFile(file->getPath().c_str());
}

void Client::uploadFile(const char* fileName){
    sendFileToServer(fileName);
}

fileData* Client::sendVersionNumberToClient(int n) {
    cout<<"heeeeeeeeeeeeeeeeeeeeeeyyyyyyyyyyyyyyyyyyyy"<<endl;
    fileData* toSend = new fileData;cout<<"1"<<endl;
    int totalSize = 8;cout<<"2"<<endl;
    int version_number =n;cout<<"3"<<endl;
    toSend->size = totalSize;cout<<"4"<<endl;
    toSend->buffer = new char[toSend->size];
    memcpy(toSend->buffer,&totalSize,4);cout<<"5"<<endl;
    memcpy(toSend->buffer+4,&version_number,4);
    cout<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<<endl;
    return toSend;
}

bool Client::shareFile(string filepath, string username) {
    sendMessageToServer(SHARE_REQUEST);
    fileData* file = writeSharingDetails(filepath, username);
    sendFileDataToServer(file);
    serverToClientMessage msg = recieveMessageFromServer();
    if(msg == OK) {
        return true;
    } else {
        return false;
    }

}

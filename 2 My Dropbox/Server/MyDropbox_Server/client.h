#ifndef CLIENT_H
#define CLIENT_H

#include "MyDefines.h"
#include "structures.h"
#include "user.h"

#include<vector>
#include<string>
using namespace std;

class Client{
    private:
        int newsockfd;
        User user;
    public:
        Client(int);

        void writeFileDataToFile(fileData*);            //write fileData to a new file in system
        fileData* recieveFile();                   //recieve Login details file from client
        clientToServerMessage recieveMessage();         //recieve message from client
        void handleMessage(clientToServerMessage);      // handle the message //and return message to server
        void sendMessage(serverToClientMessage);        // send message to client
        void sendFileData(fileData*);                   // send fileData to client
        void closeConnection();                         // close the connection
        bool validateClient();
        bool registerNewUser(User);
        void create_Table_For_New_User(User);
        void addFileToTable(string);
        fileData* readFromClient(int);                   // read n bytes from client side in a fileData
        void handleLoginRequest();
        void handleUploadRequest();
        void handleRegisterRequest();
};

#endif

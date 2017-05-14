/**
 * \class
 * \brief This class provide connection between server and user.
 *
 */
#ifndef CLIENT_H
#define CLIENT_H

#include "MyDefines.h"
#include "structures.h"
#include "File.h"

#include <string>
using namespace std;

class Client{
    private:
        int sockfd;
        //User user;
    public:
        Client(); ///<Constructor
        Client(char*, char*);
        void connectToServer(char*, char*);

        //send functions
        void sendFileToServer(const char*);
        void sendMessageToServer(clientToServerMessage);
        void sendFileDataToServer(fileData*);
        void sendFileDetails(File*);
        void uploadFile(File*);        // upload file pointed to by File* to server
        void uploadFile(const char*);  // upload file with given name to server
        fileData* sendVersionNumberToClient(int);

        // recieve functions
        fileData* recieveFileFromServer();              // similar function at server also
        serverToClientMessage recieveMessageFromServer();
        fileData* readFromServer(int);                  // read n bytes from server
        void handleMessage(serverToClientMessage);

        //validation of user
        bool checkLogin(string, string);
        bool registerUser(string, string, string);

        bool shareFile(string, string);

        void closeConnection();
};

#endif // CLIENT_H

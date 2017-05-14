#include "client.h"
#include "serverUtility.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <QSqlQuery>
#include <QSqlDatabase>
#include <QtSql>

#include <iostream>
using namespace std;



Client::Client(int newsockfd){
    this->newsockfd = newsockfd;
}

void Client::addFileToTable(string fileName){

}

void Client::writeFileDataToFile(fileData* data){
    string outputFileName = getOutputFileName(data);
    writeToFile(outputFileName.c_str(),data);
}

fileData* Client::recieveFile() {
    cout<<"------------------Entering recieveFile()----------------"<<endl;
    fileData* data = readFromClient(4);
    int sizeOfFile = getInt(data);
    delete data;
    data = readFromClient(sizeOfFile-4);
    cout<<"------------------Exiting recieveFile()-----------------"<<endl;
    return data;
}

clientToServerMessage Client::recieveMessage(){
    cout<<"Recieving message"<<endl;
    int a = getInt(readFromClient(4));
    clientToServerMessage msg;
    memcpy(&msg,&a,sizeof(msg));
    return msg;
}

void Client::create_Table_For_New_User(User newUser){
    QSqlQuery query;
    QString table_name = QString::fromStdString(newUser.getUsername());
    QString prepare_query = "CREATE TABLE "+ table_name + "( File varchar , Update_time varchar , Owner varchar, Latest_version Int )" ;
    cout<<prepare_query.toStdString()<<endl;
    query.prepare(prepare_query);
    query.exec();
    cout<<"table created for new user"<<endl;
}

void Client::handleMessage(clientToServerMessage msg){
    switch (msg) {
        case LOGIN:
        {
            cout<<"Login request"<<endl;
            handleLoginRequest();
            break;
        }
        case UPLOAD:
        {
            cout<<"Upload request"<<endl;
            handleUploadRequest();
            break;
        }
        case LOGOUT:
            cout<<"Logout request\n";
            this->closeConnection();
            break;
        case REGISTER:
        {   cout<<"Register Request"<<endl;
            handleRegisterRequest();
            break;
        }
        default:
            break;
    }
}

void Client::sendMessage(serverToClientMessage msg){
    cout<<"Sending message"<<msg<<endl;
    fileData* data = copyMessageToBuffer(msg);
    sendFileData(data);
    cout<<"Message "<<msg<<" sent to client successfully \n";
}

void Client::sendFileData(fileData* data){
    cout<<"--------------Entering sendFileData()----------------"<<endl;
    int bytes_Sent = 0 ;
    int toSend;
    while(true){
        toSend = std::min(DEFAULT_PACKET_SIZE,data->size-bytes_Sent);
        int n = write(newsockfd,(data->buffer)+bytes_Sent,toSend);
        cout<<"n = "<<n<<endl;
        if (n < 0){
            error("ERROR reading from socket");
        }else if(n == 0){
            cout<<"Finished sending to socket\n";
            break;
        }
        bytes_Sent += n;
    }
    cout<<"---------------Exiting sendFileData()-----------------"<<endl;
}

void Client::closeConnection(){
    close(this->newsockfd);
}

bool Client::validateClient(){
    QSqlQuery query;
    QString prepare_query = "SELECT NAME, PASSWORD FROM USERS WHERE NAME=? AND PASSWORD=?";
    query.prepare(prepare_query);
    query.addBindValue(QString::fromStdString(user.getUsername()));
    query.addBindValue(QString::fromStdString(user.getPassword()));
    query.exec();
    if(query.next()) {
        cout<<"true user"<<endl;
        return true;
    } else {
        cout<<"fake user"<<endl;
        return false;
    }
}

bool Client::registerNewUser(User user) {
    QSqlQuery query;
    QString prepare_query = "SELECT NAME FROM USERS WHERE NAME=?";
    query.prepare(prepare_query);
    query.addBindValue(QString::fromStdString(user.getUsername()));
    query.exec();
    if(query.next()) {
        cout<<"Username already exists"<<endl;
        return false;
    } else {
        prepare_query = "INSERT INTO USERS (NAME, PASSWORD, EMAIL) VALUES(?,?,?)";
        query.prepare(prepare_query);
        query.addBindValue(QString::fromStdString(user.getUsername()));
        query.addBindValue(QString::fromStdString(user.getPassword()));
        query.addBindValue(QString::fromStdString(user.getEmail()));
        query.exec();
        cout<<user.getUsername()<<" is registered!!"<<endl;
        return true;
    }
}

fileData* Client::readFromClient(int bytesToRead){
    fileData* data = new fileData();
    data->buffer = new char[bytesToRead];
    data->size = bytesToRead;

    int bytesRead = 0;
    while(bytesRead < bytesToRead){
        int n = read(this->newsockfd,(data->buffer)+bytesRead,std::min(DEFAULT_PACKET_SIZE,bytesToRead-bytesRead));
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

void Client::handleLoginRequest(){
    fileData *data = recieveFile();

    this->user = readLoginDetails(data);
    delete data;
    cout<<"Username: "<<this->user.getUsername()<<endl;
    cout<<"Password: "<<this->user.getPassword()<<endl;

    if(validateClient()){
        sendMessage(OK);
        //send file list (in fileData)
    }else{
        sendMessage(NOT_OK);
    }
}

void Client::handleUploadRequest(){
    fileData *data = recieveFile();
    writeFileDataToFile(data);
}

void Client::handleRegisterRequest(){
    fileData* f = recieveFile();

    User newUser = readRegisterDetails(f);
    cout<<newUser.getUsername()<<endl;
    delete f;
    if (registerNewUser(newUser)) {
        sendMessage(OK);
        this->user = newUser;
        create_Table_For_New_User(this->user);
    } else {
        sendMessage(NOT_OK);
    }
}


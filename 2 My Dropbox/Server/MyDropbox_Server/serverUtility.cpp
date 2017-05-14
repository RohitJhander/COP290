#include "serverUtility.h"
#include "MyDefines.h"
#include "user.h"

#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;

void error(const char *msg){
    perror(msg);
    exit(1);
}

string getOutputFileName(fileData* data){
    int fileNameLength = getInt(data->buffer);
    string outputFileName = getString(data->buffer+4,fileNameLength);
    data->buffer = data->buffer+4+fileNameLength;
    data->size -= (4+fileNameLength);
    return outputFileName;
}

void writeToFile(const char* filename, fileData* data){
    fstream fout(filename, ios::out | ios::binary | ios::trunc);
    fout.close();
    fout.open(filename, ios::out | ios::binary | ios::trunc);
    if(!fout.is_open()){
        cout<<"Error: can not open "<<filename<<"\n";
        exit(0);
    }
    fout.write(data->buffer+4,data->size-4);
    cout<<"Data written successfully\n";
}

void printData(fileData* data){
    for(int i=0 ; i<data->size ; i++){
        cout<<data->buffer[i];
    }
    cout<<endl;
}

fileData* copyMessageToBuffer(serverToClientMessage msg){
    fileData *toReturn = new fileData;
    toReturn->size = sizeof(msg);
    toReturn->buffer = new char[toReturn->size];	//	create new buffer
    memcpy(toReturn->buffer,&msg,sizeof(msg));
    return toReturn;
}

User readLoginDetails(fileData* Input){
    cout<<"Reading Username and Password"<<endl;
    User user;

    int username_size = getInt(Input->buffer);
    user.setUsername(getString(Input->buffer+4,username_size));

    int password_size = getInt(Input->buffer+4+username_size);
    user.setPassword(getString(Input->buffer+8+username_size,password_size));

    return user;
}

User readRegisterDetails(fileData* Input){
    cout<<"Reading Username, Password and Email for register"<<endl;
    User user;

    int username_size = getInt(Input->buffer);
    user.setUsername(getString(Input->buffer+4,username_size));

    int password_size = getInt(Input->buffer+4+username_size);
    user.setPassword(getString(Input->buffer+4+username_size+4,password_size));

    int email_size = getInt(Input->buffer+4+username_size+4+password_size);
    user.setEmail(getString(Input->buffer+4+username_size+4+password_size+4,email_size));

    return user;
}

void connectDatabase(string path) {
    QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName(QString::fromStdString(path));
    if(!mydb.open()) {
        cout<<"Can't open database"<<endl;
    } else {
        cout<<"Database Connected"<<endl;
    }
}

int getInt(fileData* data){
    if(data->size != 4){
        cout << "Error: size of data not equal to 4 bytes" << endl;
        exit(0);
    }
    return getInt(data->buffer);
}

int getInt(char* buffer){
    if(buffer == NULL){
        cout << "Error: buffer is Null" << endl;
        exit(0);
    }
    int a;
    memcpy(&a,buffer,4);
    return a;
}

string getString(char* buffer,int size){
    string a;
    a.assign(buffer,buffer+size);
    return a;
}

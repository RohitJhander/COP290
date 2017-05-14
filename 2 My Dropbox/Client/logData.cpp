#include "logData.h"

#include <QSqlQuery>
#include <QSqlDatabase>
#include <QtSql>
#include <iostream>
#include <string>
using namespace std;

void connectToLogdata(string path){
        QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE");
        mydb.setDatabaseName(QString::fromStdString(path));
        if(!mydb.open()) {
            cout<<"Can't open log database"<<endl;
        } else {
            cout<<"Log database Connected"<<endl;
        }
}

void createLogFilesTable(string tableName){
    QSqlQuery query;
    QString table = QString::fromStdString(tableName);
    QString prepare_query = "CREATE TABLE "+ table +"(FilePath varchar , ModifiedTime varchar)" ;
    query.prepare(prepare_query);
    query.exec();
    cout<<"tableCreated!********************************************************************"<<endl;
}

int getLogFilesCount(string tableName){
    QSqlQuery query;
    QString table = QString::fromStdString(tableName);
    QString prepare_query = "SELECT COUNT(*) FROM "+ table;
    query.prepare(prepare_query);
    query.exec();
    if(query.next()){
        return query.value(0).toInt(0);
    }
}

void removeFileFromLogTable(string path, string tableName){
    QSqlQuery query;
    QString table = QString::fromStdString(tableName);
    QString prepare_query = "SELECT FROM "+ table +" WHERE FilePath=?";
    query.prepare(prepare_query);
    query.addBindValue(QString::fromStdString(path));
    query.exec();
    prepare_query = "DELETE FROM "+ table +" WHERE FilePath=?";
    query.prepare(prepare_query);
    query.addBindValue(QString::fromStdString(path));
    query.exec();
}

bool checkFileInLogTable(File* file,string tableName){
    QSqlQuery query;
    QString table = QString::fromStdString(tableName);
    QString filepath = QString::fromStdString(file->getPath());
    QString prepare_query = "SELECT FilePath FROM "+ table +" WHERE FilePath=?";
    query.prepare(prepare_query);
    query.addBindValue(filepath);
    query.exec();
    if(query.next()){
        return true;
    }
    return false;
 }

void insertFileIntoLogTable(File* file,string tableName){
    cout<<"inserting into table "<<tableName<<endl;
    QSqlQuery query;
    QString table = QString::fromStdString(tableName);
    QString filepath = QString::fromStdString(file->getPath());
    QString prepare_query = "INSERT INTO "+ table +" (FilePath,ModifiedTime) VALUES(?,?)";
    query.prepare(prepare_query);
    query.addBindValue(filepath);
    cout<<"ModifiedTime: "<<convertQDateTimeToQString(file->getTime()).toStdString()<<endl;
    query.addBindValue(convertQDateTimeToQString(file->getTime()));
    query.exec();
}

bool checkUserInUserTable(string username){
    QSqlQuery query;
    QString prepare_query = "SELECT user FROM CLIENTS WHERE user=?";
    query.prepare(prepare_query);
    query.addBindValue(QString::fromStdString(username));
    query.exec();
    if(query.next()){
        return true;
    }
    return false;
}

void insertUserIntoTable(string user_name){
    if(!checkUserInUserTable(user_name)){
        QSqlQuery query;
        QString prepare_query = "INSERT INTO CLIENTS (user) VALUES(?)";
        query.prepare(prepare_query);
        query.addBindValue(QString::fromStdString(user_name));
        query.exec();
        cout<<"USer added to table"<<endl;
    }else{
        cout<<"User already exist!"<<endl;
    }
}

File* removeFirstEntryFromTable(string tableName){
    File* file = new File();
    QSqlQuery query;
    QString table = QString::fromStdString(tableName);
    QString prepare_query = "SELECT * FROM "+ table;
    query.prepare(prepare_query);
    query.exec();
    if(query.next()){
        file->setPath(query.value("FilePath").toString().toStdString());
        file->setTime(convertStringToQDateTime(query.value("ModifiedTime").toString().toStdString()));
    }

    prepare_query = "DELETE FROM "+ table +" WHERE FilePath=?";
    query.prepare(prepare_query);
    query.addBindValue(QString::fromStdString(file->getPath()));
    query.exec();
    return file;
}

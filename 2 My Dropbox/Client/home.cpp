#include "home.h"
#include "ui_home.h"
#include "client.h"
#include <QFileDialog>
#include <QDebug>
#include <QSqlQuery>
#include <iostream>
#include <stdlib.h>
#include <Connection_DB.h>
#include <mainwindow.h>
#include "oldversion.h"
#include "logData.h"
#include "commonUtility.h"

home::home(QWidget *parent) :QMainWindow(parent),ui(new Ui::home)
{
    ui->setupUi(this);
    ui->label_3->setText(username);

    makeTree();
    ui->lineEdit->hide();
    ui->lineEdit_2->hide();
    this->setFixedSize(this->size());
    //QWidget::showMaximized();
    //this->resize(QWidget::size());
    //ui->treeView->setGeometry(10,100,QWidget::geometry().width()/2,this->geometry().height()-100);
    //ui->listView->setGeometry(10+this->geometry().width()/2,100,this->geometry().width()/2,this->geometry().height()-100);
    //ui->pushButton

   // Display files from database recieved from server
   // createFilesList();

}

home::~home()
{
    delete ui;
}

void home::setUsername(QString u){
    username = u;
    QString path = "../files/"+u;

    fsdir = new QFileSystemModel;
    fsdir->setRootPath(path);
    fsdir->setFilter(QDir::NoDotAndDotDot|QDir::AllDirs);
    ui->treeView->setModel(fsdir);
    ui->treeView->setRootIndex(fsdir->index(path));

    fsfile = new QFileSystemModel;
    fsfile->setRootPath(path);
    fsfile->setFilter(QDir::NoDotAndDotDot| QDir::Files);
    ui->listView->setModel(fsfile);
    ui->listView->setRootIndex(fsfile->index(path));

    clickedFolder = fsdir->index(path+"/root");
    ui->label_5->setText("User : " + u);
}

/*******************************************************
                   UPLOAD FILE
*******************************************************/
void home::on_pushButton_2_clicked()
{
    /*QString fileName = QFileDialog::getOpenFileName(this,
    tr("Open Image"), "/home/jana", tr("Image Files (*.mp4 *.* *.png *.jpg *.bmp)"));
    */

    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setNameFilter(tr("Images (*.* *.png *.xpm *.jpg)"));
    dialog.setViewMode(QFileDialog::Detail);
    QStringList fileName;
    if (dialog.exec()){

        fileName = dialog.selectedFiles();
        path = fileName.first();


        string oldpath = path.toStdString();
        string newpath = fsdir->fileInfo(clickedFolder).absoluteFilePath().toStdString();

        system(("cp \""+ oldpath + "\" " + "\""+newpath +"\"").c_str());

        newpath = newpath + "/" + fsdir->fileName(fsdir->index(path)).toStdString();
        File* file = getFileFromPath(newpath);

        if(online) {
            uploadSync(file);
        } else {
            offlineUploadSync(file);
        }
    }

}

void home::setClient(Client* client){
    this->client = client;
}


void home::makeTree() {

}

/*****************************************
                LOG OUT
*****************************************/

void home::on_pushButton_3_clicked() //logout
{
    if(online) {client->sendMessageToServer(LOGOUT);}
    this->close();
}

void home::on_home_destroyed()
{
    client->sendMessageToServer(LOGOUT);
}

void home::on_treeView_clicked(const QModelIndex &index)
{
    QString q = fsdir->fileInfo(index).absoluteFilePath();
    ui->listView->setRootIndex(fsfile->setRootPath(q));
    clickedFolder = index;
}

void home::on_listView_clicked(const QModelIndex &index)
{
    selectedFile = index;
}

string home::getPathOfSelectedFile() {
    return fsfile->fileInfo(selectedFile).absoluteFilePath().toStdString();
}

void home::on_listView_doubleClicked(const QModelIndex &index) //opening a file
{
    QString q = fsfile->fileInfo(index).absoluteFilePath();
    if (!fsfile->fileInfo(index).isDir()) {
        QDateTime oldTime = fsfile->lastModified(index);
        QDesktopServices::openUrl(QUrl(q, QUrl::TolerantMode));
        /*cout<<"hello"<<endl;
        QDateTime newTime = fsfile->lastModified(index);
        if (newTime != oldTime) {
            File* file = getFileFromPath(fsfile->filePath(index).toStdString());
            if (online) uploadSync(file); else offlineUploadSync(file);
            system("rm *.*~");
        }*/
    }
}

void home::on_pushButton_clicked() //old Versions button
{
    //check whether a file is selected or not
    if(!selectedFile.isValid()) return;
    if(online) {
        OldVersion *oldVersion = new OldVersion();
        oldVersion->setClient(this->client);
        client->sendMessageToServer(SEE_PREVIOUS_VERSION);
        File *file = getFileFromPath(fsfile->filePath(selectedFile).toStdString());
        client->sendFileDetails(file);
        int n = getInt(client->recieveFileFromServer());
        oldVersion->setListData(n,fsfile->filePath(selectedFile));
        oldVersion->show();
    }
}

void home::on_pushButton_5_clicked() //Delete File
{
    if (online) {
        //client->deleteFileFromServer(fsfile->filePath(selectedFile));
    } else {
        //write deletion log
        File* file = getFileFromPath(fsfile->filePath(selectedFile).toStdString());

        //check file->time, not showing modifiedTime in deletedFiles table

        // if present in uploadedFiles table also, remove from there
        if(checkFileInLogTable(file,"UploadedFiles")){
            removeFileFromLogTable(file->getPath(),"UploadedFiles");
        }

        // now insert into deletedFiles table
        insertFileIntoLogTable(file,"DeletedFiles");
    }
    fsfile->remove(selectedFile);
    selectedFile = fsfile->index(fsfile->rootPath());

}

File* home::getFileFromPath(string path) {
    File* file = new File();
    file->setPath(path);
    file->setTime(fsdir->fileInfo(fsdir->index(QString::fromStdString(path))).lastModified());
    return file;
}

void home::setOnline(bool status) {
    this->online = status;
}

bool home::isOnline() {
    return this->online;
}

void home::on_pushButton_4_clicked()
{
    ui->pushButton_4->hide();
    ui->lineEdit_2->show();
    //fsdir->index
}

void home::sync(){
    syncUploadTable();
    //syncDeleteTable();
    //syncTable("ExtraFiles");
}

void home::syncDeleteTable(){
    cout<<"syncDeleteTable() "<<endl;
    string tableName = "DeletedFiles";
    cout<<tableName<<" sync finished"<<endl;
}

void home::syncUploadTable(){
    cout<<"syncUploadTable() "<<endl;
    string tableName = "UploadedFiles";

    while(getLogFilesCount(tableName) > 0){
        File* file = removeFirstEntryFromTable(tableName);
        uploadSync(file);
    }
    cout<<tableName<<" sync finished"<<endl;
}

void home::on_pushButton_6_clicked() //share button
{
    if(online && selectedFile.isValid()) ui->lineEdit->show();
}

void home::on_lineEdit_returnPressed() //share username line edit
{
    bool b = client->shareFile(fsfile->filePath(selectedFile).toStdString(), ui->lineEdit->text().toStdString());
    if (b) {
        ui->label_3->setText("Shared!");
        ui->lineEdit->hide();
    } else {
        ui->label_3->setText("Username does not exists");

    }
}

void home::uploadSync(File* file){
    client->sendMessageToServer(PUSH_FILE);
    client->sendFileDetails(file);
    serverToClientMessage msg = client->recieveMessageFromServer();
    if(msg == FILE_NOT_PRESENT){
        cout<<"file not present"<<endl;
        client->sendMessageToServer(UPLOAD_THIS_FILE);
        client->sendFileToServer(file->getPath().c_str());
    }else{
        cout<<"file present at server"<<endl;
        msg= client->recieveMessageFromServer();
        if(msg == SEND_UPDATED_FILE){
            cout<<"sending updated file"<<endl;
            client->sendFileToServer(file->getPath().c_str());
        }else if(msg == RECIEVE_UPDATED_FILE){
            //recieve updated file
        }
    }
}

void home::on_lineEdit_2_returnPressed()
{
    fsdir->mkdir(clickedFolder,ui->lineEdit_2->text());
}

void home::on_lineEdit_2_selectionChanged()
{
    ui->lineEdit_2->hide();
    ui->pushButton_4->show();
}

void home::offlineUploadSync(File* file) {

     /* check existence of file in table before inserting otherwise duplicate entries
        first delete existing entry from table  */

    if(checkFileInLogTable(file,"UploadedFiles")){
        removeFileFromLogTable(file->getPath(),"UploadedFiles");
    }

    // check in deleted file table also, if present remove from there too
    if(checkFileInLogTable(file,"DeletedFiles")){
        removeFileFromLogTable(file->getPath(),"DeletedFiles");
    }

    // now insert it into table
    insertFileIntoLogTable(file,"UploadedFiles");
    cout<<"File Inserted"<<endl;
}

void home::syncSharedWithMe() {
    //cout<<"Sync sharing##############################"<<endl;
    serverToClientMessage msg = client->recieveMessageFromServer();
    int username_size, filename_size;
    string username, fileName;
    string myPath = "../files/" + (this->username.toStdString()) + "/";  //../files/userA/
    cout<<myPath<<endl;
    while(msg == OK) {
        cout<<"#####LOOPPPING#####"<<endl;
        //recieve file
        fileData* data = client->recieveFileFromServer();
        username_size = getInt(data->buffer);
        username = getString(data->buffer + 4, username_size);
        cout<<username<<endl;
        system(("mkdir -p "+ myPath + username + "_Shared").c_str());

        filename_size = getInt(data->buffer + 4 + username_size);
        fileName = getString(data->buffer+4+username_size+4,filename_size);
        delete data;
        data = client->recieveFileFromServer();
        cout<<fileName<<endl;
        writeToFile((myPath + username+"_Shared/" + fileName).c_str(),data);

        //next file
        msg = client->recieveMessageFromServer();
    }
    cout<<"done syncing sharing !"<<endl;

}

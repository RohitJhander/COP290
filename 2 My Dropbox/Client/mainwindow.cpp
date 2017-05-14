#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Connection_DB.h"
#include "logData.h"
#include "Ufunctions.h"
#include <QtSql>
#include <QSqlDatabase>
#include <QTableWidget>
#include <QSqlQuery>
#include <QFileInfo>
#include <iostream>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->frame->hide();
    ui->label->setGeometry(0,0,450,450);
    this->setFixedHeight(450);
    this->setFixedWidth(480);

    client = NULL;

    this->show();

    fs = new QFileSystemModel;
    fs->setRootPath("../files");


    ui->frame->setGeometry(0,0,480,450);
    ui->frame_2->setGeometry(0,0,480,450);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    /*---------------LOGIN---------------*/

    if (client == NULL && !ui->checkBox->isChecked()) {
        client = new Client(serverIP,portNumber);
    }

    QString username = ui->lineEdit->text();
    QString password = ui->lineEdit_2->text();
    ui->label_15->setText("");   // register success label refresh


    if (ui->checkBox->isChecked()) {
        if(checkUserInUserTable(username.toStdString())) {
            this->close();
            hw = new home();
            hw->setUsername(username);
            hw->setOnline(false);
            hw->show();
        } else {
            ui->label_5->setText("No such User");
        }
    } else {
        client->sendMessageToServer(LOGIN);
        cout<<"Login request send\n";

        if(client->checkLogin(username.toStdString(),password.toStdString()) == true){
            cout<<fs->rootPath().toStdString()<<endl;
            system(("mkdir -p "+fs->rootPath().toStdString()+"/"+username.toStdString()+"/root").c_str());
            this->close();
            hw = new home();
            hw->setClient(client);
            hw->setUsername(username);
            hw->setOnline(true);
            hw->syncSharedWithMe();
            hw->sync();
            hw->show();
        }else{
            ui->label_5->setText("Failed to login!");
        }
    }
}

void MainWindow::on_pushButton_2_clicked() //Create Account
{
    ui->frame->show();
    ui->frame_2->hide();
}

void MainWindow::on_pushButton_3_clicked() //Submit register details
{
    QString e = validateEmail(ui->lineEdit_6, this);
    QString u = validateUsername(ui->lineEdit_5, this);
    QString p = validatePassword(ui->lineEdit_7, ui->lineEdit_3);

    ui->label_12->setText(u);
    ui->label_13->setText(e);
    ui->label_14->setText(p);

    bool valid = (e.toStdString() == "") && (u.toStdString() == "") && (p.toStdString() == "");

    if(valid) {
        if (client == NULL) {
            client = new Client(serverIP,portNumber);
        }

        QString username = ui->lineEdit_5->text();
        QString password = ui->lineEdit_7->text();
        QString email = ui->lineEdit_6->text();

        client->sendMessageToServer(REGISTER);
        bool b = client->registerUser(username.toStdString(), password.toStdString(), email.toStdString());

        //serverToClientMessage smsg = recieveMessageFromServer(this->sockfd);
        if (b) {
            ui->label_15->setText("Registered Successfully! Login to proceed");

            fs->mkdir(fs->index(fs->rootPath()),username);
            fs->mkdir(fs->index(fs->rootPath()+"/"+username),"root");
            insertUserIntoTable(username.toStdString());
            createLogFilesTable("UploadedFiles");
            createLogFilesTable("DeletedFiles");

         } else {
            ui->label_15->setText("Not Register!");
        }

       ui->frame->hide();
       ui->frame_2->show();
    }
}

void MainWindow::on_pushButton_5_clicked() //Cancel Registration
{
    ui->frame->hide();
    ui->frame_2->show();
}

void MainWindow::on_checkBox_toggled(bool checked)
{
    if (checked) {
        ui->label_5->setText("Password Not Required");
    } else {
        ui->label_5->setText("");
    }
}

void MainWindow::setServer(char* ip, char* port) {
    this->serverIP = ip;
    this->portNumber = port;
}

void MainWindow::on_lineEdit_2_returnPressed()
{
    on_pushButton_clicked();
}

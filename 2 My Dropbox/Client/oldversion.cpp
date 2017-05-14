#include "oldversion.h"
#include "ui_oldversion.h"
#include "commonUtility.h"
#include <iostream>
using namespace std;

OldVersion::OldVersion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OldVersion)
{
    ui->setupUi(this);
}

OldVersion::~OldVersion()
{
    delete ui;
}

void OldVersion::setListData(int n, QString pathoffile) {
    this->pathoffile = pathoffile;
    ui->tableWidget->setRowCount(n);
    for(int i=1;i<=n;i++) {
     //   ui->tableWidget->setItem(i-1,0,new QTableWidgetItem(("Version "+QString::fromStdString(std::to_string(i)))));
    }
}

void OldVersion::on_tableWidget_clicked(const QModelIndex &index)
{
    // why?
}

void OldVersion::on_pushButton_2_clicked() //cancel button
{
    client->sendMessageToServer(CANCEL_RESTORE);
    this->close();
}

void OldVersion::on_tableWidget_itemClicked(QTableWidgetItem *item)
{
    selectedItem = item;
}

void OldVersion::on_pushButton_clicked() //restore button
{
    cout<<"sending request############################################"<<endl;
    client->sendMessageToServer(RESTORE_VERSION);cout<<"request sent"<<endl;
    fileData* t = client->sendVersionNumberToClient(selectedItem->row()+1);cout<<"number sent"<<endl;
    client->sendFileDataToServer(t);
    fileData* data = client->recieveFileFromServer();cout<<"file recieved"<<endl;
    writeToFile(pathoffile.toStdString().c_str(),data);cout<<"done"<<endl;
    this->close();
}

void OldVersion::setClient(Client* client) {
    this->client = client;
}

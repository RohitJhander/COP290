#ifndef HOME_H
#define HOME_H

#include "client.h"

#include <QMainWindow>
#include <QListWidgetItem>
#include <string.h>
#include <QTreeWidget>
#include <QFileSystemModel>
#include <QDesktopServices>
using namespace std;

namespace Ui {
class home;
}

class home : public QMainWindow
{
    Q_OBJECT

public:
    explicit home(QWidget *parent = 0);
    void setUsername(QString);
    void setClient(Client*);
    bool isOnline();
    void setOnline(bool);
    void sync();
    void syncSharedWithMe();
    ~home();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_home_destroyed();

    void on_treeView_clicked(const QModelIndex &index);

    void on_listView_clicked(const QModelIndex &index);

    void on_listView_doubleClicked(const QModelIndex &index);

    void on_pushButton_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_6_clicked();

    void on_lineEdit_returnPressed();

    void on_lineEdit_2_returnPressed();

    void on_lineEdit_2_selectionChanged();

private:
    Ui::home *ui;
    Client* client;
    QString path;
    QString username;
    void createFilesList();
    void makeTree();
    QFileSystemModel* fsdir;
    QFileSystemModel* fsfile;
    QModelIndex clickedFolder;
    QModelIndex selectedFile;
    string getPathOfSelectedFile();
    File* getFileFromPath(string);
    bool online;
    void syncUploadTable();
    void uploadSync(File*);
    void syncDeleteTable();
    void offlineUploadSync(File*);
};

#endif // HOME_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "home.h"
#include "client.h"

namespace Ui {
class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void setServer(char*, char*);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_checkBox_toggled(bool checked);

    void on_lineEdit_2_returnPressed();

private:
    Ui::MainWindow *ui;
    home *hw;
    Client* client;
    QFileSystemModel* fs;
    char* serverIP;
    char* portNumber;
 };
#endif // MAINWINDOW_H

#ifndef OLDVERSION_H
#define OLDVERSION_H

#include <QDialog>
#include <QTableWidgetItem>
#include "client.h"

namespace Ui {
class OldVersion;
}

class OldVersion : public QDialog
{
    Q_OBJECT

public:
    explicit OldVersion(QWidget *parent = 0);
    void setListData(int, QString);
    void setClient(Client*);
    ~OldVersion();

private slots:
    void on_tableWidget_clicked(const QModelIndex &index);

    void on_pushButton_2_clicked();

    void on_tableWidget_itemClicked(QTableWidgetItem *item);

    void on_pushButton_clicked();

private:
    Ui::OldVersion *ui;
    QTableWidgetItem* selectedItem;
    Client* client;
    QString pathoffile;

};

#endif // OLDVERSION_H

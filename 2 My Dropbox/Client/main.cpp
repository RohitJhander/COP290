#include "mainwindow.h"
#include "logData.h"
#include "Connection_DB.h"
#include <QApplication>

#include "client.h"

int main(int argc, char *argv[])
{
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    connectToLogdata("log.db");
    QApplication a(argc, argv);
    MainWindow w;
    w.setServer(argv[1], argv[2]);
    //w.show();
    return a.exec();
}

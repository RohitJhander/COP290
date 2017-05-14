#include "homewindow.h"
#include "ui_homewindow.h"


HomeWindow::HomeWindow(QWidget *parent) :
    QMainWindow(parent),
    gui(new Gi::HomeWindow)
{
    gui->setupUi(this);
}

HomeWindow::~HomeWindow()
{
    delete gui;
}

#ifndef HOMEWINDOW_H
#define HOMEWINDOW_H

#include <QMainWindow>


namespace Gi {
class HomeWindow;
}

class HomeWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit HomeWindow(QWidget *parent = 0);
    ~HomeWindow();

private slots:

private:
    Gi::HomeWindow *gui;
};

#endif // HOMEWINDOW_H

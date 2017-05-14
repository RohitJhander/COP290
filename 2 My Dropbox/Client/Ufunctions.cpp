#include "Ufunctions.h"

QString validateEmail(QLineEdit* q, QObject* a) {
    QString Err ="";
    if(q->text().toStdString() == ""){
        Err ="Enter Email";
    }else{
        QRegExp rx_email("[a-zA-Z]([a-zA-Z0-9])*[@][a-zA-Z]+([.][a-zA-Z]+)+");
        q->setValidator(new QRegExpValidator(rx_email, a));
        if(!q->hasAcceptableInput()){
            Err = "Invalid Email";
        }
    }
    return Err;
}

QString validateUsername(QLineEdit* q, QObject* a) {
    QString Err ="";
    if(q->text().toStdString() == ""){
        Err ="Enter Username";
    }else{
        QRegExp rx_username("[a-zA-Z][a-zA-Z0-9]*");
        q->setValidator(new QRegExpValidator(rx_username, a));
        if(!q->hasAcceptableInput()){
            Err = "Invalid Username";
        }
    }
    return Err;
}

QString validatePassword(QLineEdit* q, QLineEdit* q2){
    QString Err = "";
    if (q->text().toStdString() == "") {
        Err = "Enter Password";
    } else if (q->text().toStdString().length() < 8) {
        Err = "Minimum 8 characters";
    }else if (q->text().toStdString().length() > 15) {
        Err = "Maximum 15 characters";
    }
    if (q->text() != q2->text()) {
        if (Err != "") {
            Err = Err + ", Passwords mismatch!";
        } else {
            Err = "Passwords mismatch!";
        }
    }
    return Err;
}

void clear_label(QLabel *q){
    q->setText("");
}

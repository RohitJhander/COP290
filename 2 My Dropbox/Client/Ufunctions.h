#ifndef UFUNCTIONS_H
#define UFUNCTIONS_H
#include <QRegExp>
#include <QLabel>
#include <string.h>
#include <QLineEdit>
#include <QRegExpValidator>

using namespace std;

QString validateEmail(QLineEdit*, QObject*) ;
QString validateUsername(QLineEdit*, QObject*);
QString validatePassword(QLineEdit*, QLineEdit*);
void clear_label(QLabel*);

#endif // UFUNCTIONS_H

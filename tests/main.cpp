#ifndef RUNNING_TESTS

#include "mainwindow.h"
#include "authenticationwindow.h"
#include "loginwindow.h"
#include "signupwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AuthenticationWindow w;
    w.show();
    return a.exec();
}

#endif

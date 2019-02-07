/*
 *  main.cpp
 *
 *  Created on: Jan 31, 2019
 *      Author: Linjuan
 */

#include "welcomewindow.h"
#include <QApplication>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    WelcomeWindow welcomeWindow;
    welcomeWindow.showMaximized();


    return app.exec();
}

#include "welcomewindow.h"
#include <QApplication>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    WelcomeWindow welcomeWindow;
    welcomeWindow.showMaximized();


    return app.exec();
}

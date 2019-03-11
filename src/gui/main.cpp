#include <QApplication>
#include "welcome_window.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    Network network;
    Assistant assistant;
    Scheduler scheduler;
    DataSaver datasaver;
    Classifier classifier(scheduler, datasaver, network, assistant);
    //unique_ptr<Classifier> classifier= make_unique<Classifier>( &scheduler,  &datasaver, &network, &assistant);
    WelcomeWindow welcomeWindow(assistant, scheduler, datasaver, classifier);
    welcomeWindow.showMaximized();

    return app.exec();
}

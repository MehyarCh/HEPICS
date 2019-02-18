#include "main_window.h"

#include <QApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow (parent)
{
    // set the size of main window
    setFixedSize(1000, 800);

    // initialize the assistant, data saver and scheduler
    assistant = new Assistant("GUI/main_window.cpp");
    classifier = new Classifier();
    datasaver = new DataSaver();
    scheduler = new Scheduler(100);  // param: int number of units

    // set the platform mode section
    pmsection = new Platform_Mode_Section(this);
    pmsection->setGeometry(0, 0, 425, 230);

    // set the image section
    isection = new ImageSection(this);
    isection->setGeometry(0, 230, 425, 570);

    // set the control section
    csection = new ControlSection(this);
    csection->setGeometry(425, 0, 575, 800);

}

Assistant* MainWindow::getAssistant()
{
	return assistant;
}
Classifier* MainWindow::getClassifier()
{
	return classifier;
}

DataSaver* MainWindow::getDataSaver()
{
	return datasaver;
}

Scheduler* MainWindow::getScheduler()
{
	return scheduler;
}

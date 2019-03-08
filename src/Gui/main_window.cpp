#include "main_window.h"

#include <QApplication>

using namespace hepics;

MainWindow::MainWindow(Assistant& assistant, Scheduler& scheduler,
		DataSaver& datasaver, Classifier& classifier)
    : QMainWindow (), assistant {assistant}, scheduler {scheduler}, datasaver {datasaver}, classifier {classifier}
{
    // set the size of main window
    setFixedSize(1000, 800);

    // initialize the assistant, data saver and scheduler

    // set the image section
    isection = new ImageSection(this);
    isection->setGeometry(0, 230, 425, 570);

    // set the control section
    csection = new ControlSection(this);
    csection->setGeometry(425, 0, 575, 800);

    // set the platform mode section
    pmsection = new Platform_Mode_Section(this);
    pmsection->setGeometry(0, 0, 425, 230);

}
Assistant &MainWindow::getAssistant(){
	return this->assistant;
}
Classifier &MainWindow::getClassifier(){
	return this->classifier;
}
DataSaver &MainWindow::getDataSaver(){
	return this->datasaver;
}
Scheduler &MainWindow::getScheduler(){
	return this->scheduler;
}


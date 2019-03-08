#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "platform_mode_section.h"
#include "image_section.h"
#include "control_section.h"
#include <QMainWindow>
#include "Assistant.h"
#include "DataSaver.h"
#include "Classifier.h"
#include "Scheduler.h"

namespace Ui {
    class MainWindow;
}
using namespace hepics;
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
	explicit MainWindow(Assistant& assistant, Scheduler& scheduler,
				DataSaver& datasaver, Classifier& classifier);
    Assistant &getAssistant();
    Classifier &getClassifier();
    DataSaver &getDataSaver();
    Scheduler &getScheduler();

private:
    Assistant& assistant;
    Scheduler& scheduler;
    DataSaver& datasaver;
    Classifier& classifier;

    Platform_Mode_Section *pmsection;
	ImageSection *isection;
    ControlSection *csection;


};

#endif // MAINWINDOW_H

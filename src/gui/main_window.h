#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "platform_mode_section.h"
#include "image_section.h"
#include "control_section.h"
#include <QMainWindow>
#include "../hepics/Assistant.h"
#include "../hepics/DataSaver.h"
#include "../hepics/Classifier.h"
#include "../hepics/Scheduler.h"

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
    Platform_Mode_Section *get_pmsection();
    ImageSection *get_isection();
    ControlSection *get_csection();

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

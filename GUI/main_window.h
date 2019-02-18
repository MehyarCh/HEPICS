#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "platform_mode_section.h"
#include "image_section.h"
#include "control_section.h"
#include <QMainWindow>
#include "HepicsModel/src/Assistant.h"
#include "HepicsModel/src/Classifier.h"
#include "HepicsModel/src/DataSaver.h"
#include "HepicsModel/src/Scheduler.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);

    Assistant* getAssistant();
    Classifier* getClassifier();
    DataSaver* getDataSaver();
    Scheduler* getScheduler();

private:
    Assistant *assistant;
    Classifier *classifier;
    DataSaver *datasaver;
    Scheduler *scheduler;

    Platform_Mode_Section *pmsection;
    ImageSection *isection;
    ControlSection *csection;
};

#endif // MAINWINDOW_H

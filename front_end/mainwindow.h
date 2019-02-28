/*
 * mainwindow.h
 *
 *  Created on: Jan 31, 2019
 *      Author: Linjuan
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "platform_mode_section.h"
#include "imagesection.h"
#include "controlsection.h"
#include <QMainWindow>
#include "Assistant.h"
#include "Classifier.h"
#include "DataSaver.h"
#include "Scheduler.h"

namespace Ui {
    class MainWindow;
}

using namespace hepics;
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(Assistant& assistant, Classifier& classifier, DataSaver& datasaver, Scheduler& scheduler);

private:
    Assistant assistant;
    Classifier classifier;
    DataSaver datasaver;
    Scheduler scheduler;
    Platform_Mode_Section *pmsection;
    ImageSection *isection;
    ControlSection *csection;
};

#endif // MAINWINDOW_H

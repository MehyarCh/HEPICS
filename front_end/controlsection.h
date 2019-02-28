/*
 * controlsection.h
 *
 *  Created on: Jan 31, 2019
 *      Author: Linjuan
 */

#ifndef CONTROLSECTION_H
#define CONTROLSECTION_H

#include <QMainWindow>
#include <QProgressBar>
#include <QLabel>
#include <QPushButton>
#include "Assistant.h"
#include "Classifier.h"
#include "DataSaver.h"

namespace Ui
{
    class ControlSection;
}

using namespace hepics;
class ControlSection : public QWidget
{
    Q_OBJECT
public:
    ControlSection(Assistant assistant, DataSaver datasaver, Classifier classifier);

public slots:
    void startCancelProcess();
    void pauseResumeProcess();
    void aggregateResult();
    void showResult();

private:
    QProgressBar*progressbar;
    QLabel *result;

    QPushButton *button_aggregate;
    QPushButton *button_pause_resume;
    QPushButton *button_start_cancel;

    Assistant assistant;
    DataSaver datasaver;
    Classifier classifier;
}
#endif // CONTROLSECTION_H

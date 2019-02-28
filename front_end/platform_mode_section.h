/*
 * platform_mode_section.h
 *
 *  Created on: Jan 31, 2019
 *      Author: Linjuan
 */

#ifndef PLATFORM_MODE_SECTION_H
#define PLATFORM_MODE_SECTION_H

#include <QMainWindow>
#include <QCheckBox>
#include <QComboBox>
#include <QLabel>
#include "Scheduler.h"

namespace Ui {
    class Platform_Mode_Section;
}

using namespace hepics;

class Platform_Mode_Section : public QWidget
{
    Q_OBJECT
public:
    explicit Platform_Mode_Section(Scheduler& scheduler);
public slots:
    void enableModeComboBox(int);
    void setOperationMode();
private:
    QLabel *text_platform;
    QLabel *text_operation_mode;

    QCheckBox *cbox_cpu;
    QCheckBox *cbox_gpu;
    QCheckBox *cbox_fpga;
    QComboBox *box_operation_mode;

    int counter_platform;

    Scheduler scheduler;
};

#endif // PLATFORM_MODE_SECTION_H

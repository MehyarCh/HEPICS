/*
 * platform_mode_section.cpp
 *
 *  Created on: Jan 31, 2019
 *      Author: Linjuan
 */

#include "platform_mode_section.h"

Platform_Mode_Section::Platform_Mode_Section(QMainWindow *parent)
    : QWidget (parent)
{
    // set the platform section
    text_platform = new QLabel(this);
    text_platform->setText("Choose Platform");
    text_platform->setGeometry(100, 45, 325, 45);

    cbox_cpu = new QCheckBox("CPU", this);
    cbox_cpu->setGeometry(100, 90, 90, 35);
    cbox_gpu = new QCheckBox("GPU", this);
    cbox_gpu->setGeometry(200, 90, 90, 35);
    cbox_fpga = new QCheckBox("FPGA", this);
    cbox_fpga->setGeometry(300, 90, 90, 35);

    // set the operation mode section
    text_operation_mode = new QLabel(this);
    text_operation_mode->setText("Choose Operation Mode");
    text_operation_mode->setGeometry(100, 135, 325, 45);

    box_operation_mode = new QComboBox(this);
    box_operation_mode->addItem("High Performance");
    box_operation_mode->addItem("Low Power Consumption");
    box_operation_mode->addItem("High Energy Efficiency");
    box_operation_mode->setGeometry(100, 180, 325, 35);
    box_operation_mode->setEditable(false);
    box_operation_mode->setEnabled(false);

    counter_platform = 0;

    connect(cbox_cpu, SIGNAL(stateChanged(int)), this, SLOT(enableModeComboBox(int)));
    connect(cbox_gpu, SIGNAL(stateChanged(int)), this, SLOT(enableModeComboBox(int)));
    connect(cbox_fpga, SIGNAL(stateChanged(int)), this, SLOT(enableModeComboBox(int)));

}

void Platform_Mode_Section::enableModeComboBox(int state)
{
    counter_platform += (state - 1);

    if (counter_platform >= 2) {
        box_operation_mode->setEnabled(true);
    } else {
        box_operation_mode->setEnabled(false);
    }
}


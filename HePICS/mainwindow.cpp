/*
 * mainwindow.cpp
 *
 *  Created on: Jan 31, 2019
 *      Author: Linjuan
 */

#include <QApplication>
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow (parent)
{
    // set the size of main window
    setFixedSize(1000, 800);

    pmsection = new Platform_Mode_Section(this);
    pmsection->setGeometry(0, 0, 425, 230);

    // set the image section
    isection = new ImageSection(this);
    isection->setGeometry(0, 230, 425, 570);

    // set the control section
    csection = new ControlSection(this);
    csection->setGeometry(425, 0, 575, 800);

}

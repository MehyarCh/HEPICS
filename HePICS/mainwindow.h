#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "platform_mode_section.h"
#include "imagesection.h"
#include "controlsection.h"
#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);

private:
    Platform_Mode_Section *pmsection;
    ImageSection *isection;
    ControlSection *csection;
};

#endif // MAINWINDOW_H

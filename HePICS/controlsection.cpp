#include "controlsection.h"

ControlSection::ControlSection(QMainWindow *parent)
    : QWidget (parent)
{
    // set the progress bar
    progressbar = new QProgressBar(this);
    progressbar->setRange(0, 100);
    progressbar->setValue(0);
    progressbar->setOrientation(Qt::Horizontal);
    progressbar->setGeometry(125, 55, 400, 35);

    // set the result section
    result = new QLabel(this);
    result->setStyleSheet("border: 1px solid black");
    result->setGeometry(125, 120, 400, 400);

    // set the control section
    button_aggregate = new QPushButton("Aggregate", this);
    button_start_cancel = new QPushButton("Start", this);
    button_pause_resume = new QPushButton("Pause", this);

    button_aggregate->setGeometry(280, 592, 90, 30);
    button_start_cancel->setGeometry(155, 650, 90, 30);
    button_pause_resume->setGeometry(405, 650, 90, 30);

    connect(button_aggregate, SIGNAL(clicked()), this, SLOT(aggregateResult()));
    connect(button_start_cancel, SIGNAL(clicked()), this, SLOT(startCancelProcess()));
    connect(button_pause_resume, SIGNAL(clicked()), this, SLOT(pauseResumeProcess()));
}

void ControlSection::startCancelProcess()
{
    if(button_start_cancel->text() == "Start") {
        // Start the Process


        button_start_cancel->setText("Cancel");
    } else {
        // Cancel the Process

        button_start_cancel->setText("Start");
    }
}

void ControlSection::pauseResumeProcess()
{

    if (button_pause_resume->text() == "Pause") {
        // Pause the Process

        button_pause_resume->setText("Resume");
    } else {
        // Resume the Process

        button_pause_resume->setText("Pause");
    }
}

void ControlSection::aggregateResult()
{
    // aggregate the result
}

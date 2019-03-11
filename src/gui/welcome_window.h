#ifndef WELCOMEWINDOW_H
#define WELCOMEWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>

#include "main_window.h"

namespace Ui {
    class WelcomeWindow;
}

class WelcomeWindow : public QMainWindow
{
    Q_OBJECT
public:
	explicit WelcomeWindow(Assistant& assistant, Scheduler& scheduler,
			DataSaver& datasaver, Classifier& classifier);
public slots:
    void openMainWindow();
private:
    Assistant& assistant;
	Scheduler& scheduler;
	DataSaver& datasaver;
	Classifier& classifier;
    MainWindow *m_mainwindow;
    QLabel *m_text;
    QLabel *m_icon;
    QPushButton *m_button;
};

#endif // WELCOMEWINDOW_H

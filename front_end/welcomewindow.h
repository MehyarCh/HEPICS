/*
 * welcomewindow.h
 *
 *  Created on: Jan 31, 2019
 *      Author: Linjuan
 */
 
#ifndef WELCOMEWINDOW_H
#define WELCOMEWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include "mainwindow.h"

namespace Ui {
    class WelcomeWindow;
}

class WelcomeWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit WelcomeWindow(MainWindow *main_window);
public slots:
    void handleButton();
private:
    MainWindow *m_mainwindow;
    QLabel *m_text;
    QLabel *m_icon;
    QPushButton *m_button;
};

#endif // WELCOMEWINDOW_H

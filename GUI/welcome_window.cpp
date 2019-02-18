#include <QApplication>
#include "main_window.h"
#include "welcome_window.h"

WelcomeWindow::WelcomeWindow(QWidget *parent)
    : QMainWindow (parent)
{
    // set the size of welcome window
    setFixedSize(1000, 800);

    // the label which contains the introduction of HePICS
    m_text = new QLabel(this);
    m_text->setText("Welcome!\n\nHePICS is an image classification system which uses AlexNet as a pre-trained neural network model");
    m_text->setGeometry(75, 50, 850, 250);
    m_text->setAlignment(Qt::AlignCenter);
    m_text->setWordWrap(true);

    // change the font size of the text
    QFont font = m_text->font();
    font.setPointSize(25);
    m_text->setFont(font);
    // change the backgroung-color of this label
    m_text->setStyleSheet("background-color:rgb(255, 255, 255)");


    // the label which contains the logo of tiger
    m_icon = new QLabel(this);
    QPixmap pixmap("/home/linjuanfan/Pictures/welcome.jpg");
    m_icon->setPixmap(pixmap);
    m_icon->setScaledContents(true);
    m_icon->setGeometry(125, 400, 480, 270);

    // the button of start
    m_button = new QPushButton("Start", this);
    m_button->setGeometry(720, 525, 150, 50);

    //change the font size of the text
    QFont font2 = m_button->font();
    font2.setPointSize(20);
    m_button->setFont(font2);
    // change the backgroung-color of this button
    m_button->setStyleSheet("background-color:rgb(255, 255, 255)");

    // initialize the main window
    m_mainwindow = new MainWindow();

    // when click the start button, the main window should be opened and this window is closed
    connect(m_button, SIGNAL(clicked()), this, SLOT(openMainWindow()));
}

void WelcomeWindow::openMainWindow()
{
    m_mainwindow->show();
    this->hide();
}

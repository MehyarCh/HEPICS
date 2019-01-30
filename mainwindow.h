
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>


class MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *pauseResumePushButton;
    QPushButton *StartCancelPushButton;
    QPushButton *AggregatePushButton;
    QProgressBar *progressBar;
    QTextBrowser *resultsBrowser;
    QComboBox *choosePlatformComboBox;
    QComboBox *chooseOperationModeComboBox;
    QComboBox *chooseImageComboBox;
    QPushButton *addPushButton;
    QPushButton *deletePushButton;
    QPushButton *resetPushButton;
    QLabel *label_choosePlatform;
    QLabel *label_chooseOperationMode;
    QLabel *label_chooseImage;
    QGraphicsView *ThumbnailGraphicsView;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QMainWindow *MainWindow = new QMainWindow;

    void setupGUI();
    void setupGUI2();


};


#endif // MAINWINDOW_H

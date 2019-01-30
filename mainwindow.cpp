#include "mainwindow.h"


void MainWindow::setupGUI()
{
    if (MainWindow->objectName().isEmpty())
        MainWindow->setObjectName(QStringLiteral("MainWindow"));
    MainWindow->resize(671, 501);
    centralWidget = new QWidget(MainWindow);
    centralWidget->setObjectName(QStringLiteral("centralWidget"));
    pauseResumePushButton = new QPushButton(centralWidget);
    pauseResumePushButton->setObjectName(QStringLiteral("pauseResumePushButton"));
    pauseResumePushButton->setGeometry(QRect(530, 380, 131, 25));
    StartCancelPushButton = new QPushButton(centralWidget);
    StartCancelPushButton->setObjectName(QStringLiteral("StartCancelPushButton"));
    StartCancelPushButton->setGeometry(QRect(360, 380, 131, 25));
    AggregatePushButton = new QPushButton(centralWidget);
    AggregatePushButton->setObjectName(QStringLiteral("AggregatePushButton"));
    AggregatePushButton->setGeometry(QRect(450, 330, 131, 25));
    progressBar = new QProgressBar(centralWidget);
    progressBar->setObjectName(QStringLiteral("progressBar"));
    progressBar->setGeometry(QRect(370, 20, 291, 23));
    progressBar->setValue(0);
    resultsBrowser = new QTextBrowser(centralWidget);
    resultsBrowser->setObjectName(QStringLiteral("resultsBrowser"));
    resultsBrowser->setGeometry(QRect(370, 60, 291, 241));
    choosePlatformComboBox = new QComboBox(centralWidget);
    choosePlatformComboBox->setObjectName(QStringLiteral("choosePlatformComboBox"));
    choosePlatformComboBox->setGeometry(QRect(20, 40, 251, 25));
    chooseOperationModeComboBox = new QComboBox(centralWidget);
    chooseOperationModeComboBox->setObjectName(QStringLiteral("chooseOperationModeComboBox"));
    chooseOperationModeComboBox->setGeometry(QRect(20, 100, 251, 25));
    chooseImageComboBox = new QComboBox(centralWidget);
    chooseImageComboBox->setObjectName(QStringLiteral("chooseImageComboBox"));
    chooseImageComboBox->setGeometry(QRect(20, 160, 251, 25));
    addPushButton = new QPushButton(centralWidget);
    addPushButton->setObjectName(QStringLiteral("addPushButton"));
    addPushButton->setGeometry(QRect(20, 200, 71, 25));
    deletePushButton = new QPushButton(centralWidget);
    deletePushButton->setObjectName(QStringLiteral("deletePushButton"));
    deletePushButton->setGeometry(QRect(110, 200, 71, 25));
    resetPushButton = new QPushButton(centralWidget);
    resetPushButton->setObjectName(QStringLiteral("resetPushButton"));
    resetPushButton->setGeometry(QRect(200, 200, 71, 25));
    label_choosePlatform = new QLabel(centralWidget);
    label_choosePlatform->setObjectName(QStringLiteral("label_choosePlatform"));
    label_choosePlatform->setEnabled(true);
    label_choosePlatform->setGeometry(QRect(20, 20, 121, 17));
    label_chooseOperationMode = new QLabel(centralWidget);
    label_chooseOperationMode->setObjectName(QStringLiteral("label_chooseOperationMode"));
    label_chooseOperationMode->setGeometry(QRect(20, 80, 181, 17));
    label_chooseImage = new QLabel(centralWidget);
    label_chooseImage->setObjectName(QStringLiteral("label_chooseImage"));
    label_chooseImage->setGeometry(QRect(20, 140, 111, 17));
    ThumbnailGraphicsView = new QGraphicsView(centralWidget);
    ThumbnailGraphicsView->setObjectName(QStringLiteral("ThumbnailGraphicsView"));
    ThumbnailGraphicsView->setGeometry(QRect(20, 240, 251, 192));
    MainWindow->setCentralWidget(centralWidget);
    menuBar = new QMenuBar(MainWindow);
    menuBar->setObjectName(QStringLiteral("menuBar"));
    menuBar->setGeometry(QRect(0, 0, 671, 22));
    MainWindow->setMenuBar(menuBar);
    mainToolBar = new QToolBar(MainWindow);
    mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
    MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
    statusBar = new QStatusBar(MainWindow);
    statusBar->setObjectName(QStringLiteral("statusBar"));
    MainWindow->setStatusBar(statusBar);

    setupGUI2();

}

void MainWindow::setupGUI2()
{
    MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
    pauseResumePushButton->setText(QApplication::translate("MainWindow", "Pause/Resume", nullptr));
    StartCancelPushButton->setText(QApplication::translate("MainWindow", "Start/Cancel", nullptr));
    AggregatePushButton->setText(QApplication::translate("MainWindow", "Aggregate", nullptr));
    choosePlatformComboBox->clear();
    choosePlatformComboBox->insertItems(0, QStringList()
     << QApplication::translate("MainWindow", "FPGA", nullptr)
     << QApplication::translate("MainWindow", "CPU", nullptr)
     << QApplication::translate("MainWindow", "GPU", nullptr)
    );
    chooseOperationModeComboBox->clear();
    chooseOperationModeComboBox->insertItems(0, QStringList()
     << QApplication::translate("MainWindow", "High Performance", nullptr)
     << QApplication::translate("MainWindow", "Low Power Consumption", nullptr)
     << QApplication::translate("MainWindow", "High Energy Efficiency", nullptr)
    );
    addPushButton->setText(QApplication::translate("MainWindow", "add", nullptr));
    deletePushButton->setText(QApplication::translate("MainWindow", "delete", nullptr));
    resetPushButton->setText(QApplication::translate("MainWindow", "reset", nullptr));
    label_choosePlatform->setText(QApplication::translate("MainWindow", "Choose platform", nullptr));
    label_chooseOperationMode->setText(QApplication::translate("MainWindow", "Choose Operation Mode", nullptr));
    label_chooseImage->setText(QApplication::translate("MainWindow", "Choose Image", nullptr));
    MainWindow->show();
}

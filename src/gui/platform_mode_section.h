#ifndef PLATFORM_MODE_SECTION_H
#define PLATFORM_MODE_SECTION_H

#include <QMainWindow>
#include <QCheckBox>
#include <QComboBox>
#include <QLabel>
#include <vector>

using namespace std;

class MainWindow;

namespace Ui {
    class Platform_Mode_Section;
}

class Platform_Mode_Section : public QWidget
{
    Q_OBJECT
public:
	explicit Platform_Mode_Section(MainWindow *parent);

public slots:
    void enableModeComboBox(int);
    void setOperationMode();
private:
    MainWindow  *main_window;

    QLabel *text_platform;
    QLabel *text_operation_mode;

    QCheckBox *cbox_cpu;
    QCheckBox *cbox_gpu;
    QCheckBox *cbox_fpga;
    QComboBox *box_operation_mode;

    int counter_platform;

};

#endif // PLATFORM_MODE_SECTION_H

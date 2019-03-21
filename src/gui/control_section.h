#ifndef CONTROLSECTION_H
#define CONTROLSECTION_H

#include <QMainWindow>
#include <QProgressBar>
#include <QLabel>
#include <QPushButton>
#include <QCheckBox>
#include <QTimer>
#include "../hepics/Result.h"

namespace Ui
{
    class ControlSection;
}

class MainWindow;

class ControlSection : public QWidget
{
    Q_OBJECT
public:
    explicit ControlSection(MainWindow *parent);
    void set_result_id(int id);

public slots:
    void startCancelProcess();
    void pauseResumeProcess();
    void getResults(bool checked);
    void update_progress();

private:
    QProgressBar*progressbar;
    QLabel *result;

    MainWindow  *main_window;
    QCheckBox *button_aggregate;
    QPushButton *button_pause_resume;
    QPushButton *button_start_cancel;
    QTimer      *progress_timer;

};

#endif // CONTROLSECTION_H

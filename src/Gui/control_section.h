#ifndef CONTROLSECTION_H
#define CONTROLSECTION_H

#include <QMainWindow>
#include <QProgressBar>
#include <QLabel>
#include <QPushButton>

namespace Ui
{
    class ControlSection;
}

class ControlSection : public QWidget
{
    Q_OBJECT
public:
    explicit ControlSection(QMainWindow *parent);

public slots:
    void startCancelProcess();
    void pauseResumeProcess();
    void aggregateResult();
    void showResult();

private:
    QProgressBar*progressbar;
    QLabel *result;

    QPushButton *button_aggregate;
    QPushButton *button_pause_resume;
    QPushButton *button_start_cancel;

};

#endif // CONTROLSECTION_H

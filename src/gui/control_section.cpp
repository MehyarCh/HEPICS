#include "control_section.h"
#include <unistd.h>
#include <cmath>
#include <algorithm>
#include "main_window.h"

using namespace std;

ControlSection::ControlSection(MainWindow *parent)
:
		QWidget(parent), main_window(parent)
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

	button_start_cancel->setEnabled(true);
	button_pause_resume->setEnabled(false);

	button_aggregate->setGeometry(280, 592, 90, 30);
	button_start_cancel->setGeometry(155, 650, 90, 30);
	button_pause_resume->setGeometry(405, 650, 90, 30);

	progress_timer = new QTimer(this);
	progress_timer->setInterval(1000);

	connect(button_aggregate, SIGNAL(clicked()), this, SLOT(aggregateResult()));
	connect(button_start_cancel, SIGNAL(clicked()), this, SLOT(startCancelProcess()));
	connect(button_pause_resume, SIGNAL(clicked()), this, SLOT(pauseResumeProcess()));

	connect(progress_timer, SIGNAL(timeout()), this, SLOT(update_progress()));

}

static auto format_result(Result &res) {
	auto str = ""s;
	for (size_t i = 0, n = min(size_t { 4 }, res.get_results().size()); i < n; ++i) {
		auto &pair = res.get_results()[i];
		str += pair.first.substr(10) + ": " + to_string(uint64_t(round(pair.second * 100.0f))) + "%\n";
	}
	return str;
}

void ControlSection::set_result_id(int id) {
	auto &res = main_window->getDataSaver().get_result(id);
	if (res != nullptr) {
		result->setText(QString::fromStdString(format_result(*res)));
		result->setAlignment(Qt::AlignLeft);
		result->setWordWrap(true);
	}
}

void ControlSection::startCancelProcess()
{
	if (button_start_cancel->text() == "Start" &&
			main_window->getClassifier().start()) {
		button_start_cancel->setText("Cancel");
		button_pause_resume->setEnabled(true);
		if (button_pause_resume->text() == "Resume") {
			button_pause_resume->setText("Pause");
		}
		progress_timer->start();
	} else {
		main_window->getClassifier().cancel();
	}
}
;

void ControlSection::pauseResumeProcess()
{
	if (button_pause_resume->text() == "Pause") {
		button_pause_resume->setText("Resume");
		main_window->getClassifier().pause();
	} else {
		button_pause_resume->setText("Pause");
		main_window->getClassifier().resume();
	}
}

void ControlSection::aggregateResult()
{
	// aggregate the result
	Result res = main_window->getDataSaver().aggregate();

	// convert std::string to QString
	QString str = QString::fromStdString(format_result(res));

	// display the result with QLabel
	result->setText(str);
	result->setAlignment(Qt::AlignLeft);
	result->setWordWrap(true);
}

void ControlSection::update_progress() {
	auto &classifier = main_window->getClassifier();
	progressbar->setValue(round(classifier.get_progress() * 100.0f));
	if (!classifier.is_running()) {
		classifier.save_results();
		set_result_id(main_window->get_isection()->get_selected_id());
		if (classifier.is_canceled()) {
			progressbar->setValue(0);
		}
		button_start_cancel->setText("Start");
		button_pause_resume->setEnabled(false);
		progress_timer->stop();
	}
}


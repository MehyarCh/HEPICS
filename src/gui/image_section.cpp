#include "image_section.h"
#include "main_window.h"

ImageSection::ImageSection(MainWindow *parent)
:
		QWidget(parent), main_window(parent)
{
	// set the image section
	text_image = new QLabel(this);
	text_image->setText("Choose Image");
	text_image->setGeometry(100, 0, 325, 45);
	box_image = new QComboBox(this);
	box_image->setGeometry(100, 45, 325, 35);
	box_image->setEditable(false);

	// set the control buttons for image section
	button_add = new QPushButton("Add", this);
	button_add->setGeometry(100, 105, 90, 30);
	button_delete = new QPushButton("Delete", this);
	button_delete->setGeometry(217, 105, 90, 30);
	button_delete->setEnabled(false);
	button_reset = new QPushButton("Reset", this);
	button_reset->setGeometry(335, 105, 90, 30);
	button_reset->setEnabled(false);

	// set the thumbnails display label
	thumbnail = new QLabel(this);
	thumbnail->setGeometry(100, 175, 325, 325);
	thumbnail->setStyleSheet("border: 1px solid black");

	// initialize the file dialog
	filedialog = new QFileDialog(this);

	// initialize the list of file name of all the input images
	file_name_list = new QStringList();

	/*
	 * when add (delete, reset) button is clicked, the operation of to add(delete, reset)
	 * the item(s) of the combo box and back-end should be executed.
	 */
	connect(button_add, SIGNAL(clicked()), this, SLOT(addAnImageFile()));
	connect(button_delete, SIGNAL(clicked()), this, SLOT(deleteAnItem()));
	connect(button_reset, SIGNAL(clicked()), this, SLOT(clearAllItems()));
	// when the current text of the combo list is changed, the thumbnail of current image should be displayed
	connect(box_image, SIGNAL(currentIndexChanged(const QString)), this, SLOT(showThumbnail()));

}

static auto get_current_path(QStringList &list, QComboBox &box) {
	auto i = box.currentIndex();
	if (i >= 0 && i < list.size()) {
		return list.at(i).toStdString();
	}
	return ""s;
}

int ImageSection::get_selected_id() const {
	auto image = main_window->getAssistant().get_input_image(get_current_path(*file_name_list, *box_image));
	return image != nullptr ? image->id : -1;
}

void ImageSection::addAnImageFile()
{
	filedialog->show();

	// get the path of the image
	QStringList fileNames = QFileDialog::getOpenFileNames(
			this, tr("Open File"), "/home",
			tr("Image Files (*.jpeg *.jpg *.jpe *.png *.xpm)"));

	for (QString fileName : fileNames) {

		QStringList list = fileName.split("/");

		// if choose a image file, add a new item into the list
		if (!fileName.isNull()) {
			file_name_list->append(fileName);
			box_image->addItem(list.last());
			box_image->setCurrentIndex(box_image->count() - 1);

			// send the path of this image to the assistant
			main_window->getAssistant().add_input_map(fileName.toStdString());
			button_delete->setEnabled(true);
			button_reset->setEnabled(true);
		}
	}


	filedialog->close();
}

void ImageSection::deleteAnItem()
{
	// remove this image from back-end database
	auto path = file_name_list->at(box_image->currentIndex()).toStdString();
	auto &assistant = main_window->getAssistant();
	auto image = assistant.get_input_image(path);
	if(image != nullptr) {
		main_window->getDataSaver().delete_result(image->id);
	}
	assistant.delete_input_map(path);

	// remove its file name from the list and the item of the combo list
	file_name_list->removeAt(box_image->currentIndex());
	box_image->removeItem(box_image->currentIndex());
	if (file_name_list->size() == 0) {
		button_delete->setEnabled(false);
		button_reset->setEnabled(false);
	}
}

void ImageSection::clearAllItems()
{
	// clear all the items
	main_window->getDataSaver().clear();
	main_window->getAssistant().reset_input_map();
	file_name_list->clear();
	box_image->clear();
	button_delete->setEnabled(false);
	button_reset->setEnabled(false);
}

void ImageSection::showThumbnail()
{
	int index = (box_image->currentIndex());

	if (box_image->count() != 0 && index <= (file_name_list->count() - 1)) {
		QString path = file_name_list->at(index);
		QPixmap pixmap(path);
		thumbnail->setPixmap(pixmap);
		thumbnail->setScaledContents(true);
	} else {
		thumbnail->clear();
	}

	main_window->get_csection()->set_result_id(get_selected_id());
}

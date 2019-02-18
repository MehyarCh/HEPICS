#include "image_section.h"
#include "main_window.h"

ImageSection::ImageSection(QMainWindow *parent)
    : QWidget (parent)
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
    button_reset = new QPushButton("Reset", this);
    button_reset->setGeometry(335, 105, 90, 30);

    // set the thumbnails display label
    thumbnail = new QLabel(this);
    thumbnail->setGeometry(100, 175, 325, 325);
    thumbnail->setStyleSheet("border: 1px solid black");

    // initialize the file dialog
    filedialog = new QFileDialog(this);

    // initialize the list of file name of all the input images
    file_name_list = new QStringList();

    // initialize the assistant
    MainWindow *m_main_window = parent;
    assistant = m_main_window->getAssistant();

    /*
     * when add (delete, reset) button is clicked, the operation of to add(delete, reset)
     * the item(s) of the combo box and back-end should be executed.
     */
    connect(button_add, SIGNAL(clicked()), this, SLOT(addAnImageFile()));
    connect(button_delete, SIGNAL(clicked()), this, SLOT(deleteAnItem()));
    connect(button_reset,SIGNAL(clicked()), this, SLOT(clearAllItems()));
    // when the current text of the combo list is changed, the thumbnail of current image should be displayed
    connect(box_image, SIGNAL(currentIndexChanged(const QString)), this, SLOT(showThumbnail()));

}

void ImageSection::addAnImageFile()
{
    filedialog->show();

    // get the path of the image
    QString fileName = QFileDialog::getOpenFileName(
                this, tr("Open File"), "/home",
                tr("Image Files (*.jpeg *.jpg *.jpe *.png *.xpm)"));

    QStringList list = fileName.split("/");

    // if choose a image file, add a new item into the list
    if (!fileName.isNull()) {
        file_name_list->append(fileName);
        box_image->addItem(list.last());
        box_image->setCurrentIndex(box_image->count() - 1);
    }

    // convert QString to char array
    QByteArray ba = fileName.toLocal8Bit();
    char *result = (char *)strdup(ba.constData());

    // send the path of this image to the assistant
    assistant->addInputImage(result);


    filedialog->close();
}

void ImageSection::deleteAnItem()
{
    // remove this image from back-end database
	std::list<Image>::iterator iter = assistant->getInputs().begin();
	int i = 0;
	while (iter!= assistant->getInputs().end()
			&& i < box_image->currentIndex()) {
		iter++;
	}
	assistant->deleteImage(*iter);

	// remove its file name from the list and the item of the combo list
    file_name_list->removeAt(box_image->currentIndex());
    box_image->removeItem(box_image->currentIndex());
}

void ImageSection::clearAllItems()
{
	// clear all the items
    file_name_list->clear();
    box_image->clear();

    assistant->resetInputs();
}

void ImageSection::showThumbnail()
{
    int index = (box_image->currentIndex());

    if (box_image->count() != 0 && index <= (file_name_list->count() - 1))  {
        QString path = file_name_list->at(index);
        QPixmap pixmap (path);
        thumbnail->setPixmap(pixmap);
        thumbnail->setScaledContents(true);
    } else {
        thumbnail->clear();
    }
}

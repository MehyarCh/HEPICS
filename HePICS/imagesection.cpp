/*
 * imagesection.cpp
 *
 *  Created on: Jan 31, 2019
 *      Author: Linjuan
 */

#include "imagesection.h"

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

    // set the conotrol buttons for image section
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
    thumbnail->setStyleSheet("background-color:rgb(255, 255, 255)");

    filedialog = new QFileDialog(this);

    // connect signals with slots
    connect(button_add, SIGNAL(clicked()), this, SLOT(addAnImageFile()));
    connect(button_delete, SIGNAL(clicked()), this, SLOT(deleteAnItem()));
    connect(button_reset,SIGNAL(clicked()), box_image, SLOT(clear()));
    connect(box_image, SIGNAL(currentIndexChanged(const QString)), this, SLOT(showThumbnail()));

}

void ImageSection::addAnImageFile()
{
    filedialog->show();
    QString fileName = QFileDialog::getOpenFileName(
                this, tr("Open File"), "/home",
                tr("Image Files (*.jpeg *.jpg *.jpe *.png *.xpm)"));
    QStringList list = fileName.split("/");
    box_image->addItem(list.last());
    box_image->setCurrentIndex(box_image->count() - 1);
    QPixmap pixmap(fileName);
    thumbnail->setPixmap(pixmap);
    thumbnail->setScaledContents(true);
    filedialog->close();
}

void ImageSection::deleteAnItem()
{
    box_image->removeItem(box_image->currentIndex());
}

void ImageSection::showThumbnail()
{
    QString path = "/home/linjuanfan/Pictures/";
    path += box_image->currentText();
    QPixmap pixmap(path);
    thumbnail->setPixmap(pixmap);
    thumbnail->setScaledContents(true);
}

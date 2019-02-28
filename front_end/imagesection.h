/*
 * imagesection.h
 *
 *  Created on: Jan 31, 2019
 *      Author: Linjuan
 */

#ifndef IMAGESECTION_H
#define IMAGESECTION_H

#include <QMainWindow>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QFileDialog>
#include "Assistant.h"

namespace Ui {
    class Image_Section;
}

using namespace hepics;
class ImageSection : public QWidget
{
    Q_OBJECT
public:
    explicit ImageSection(Assistant& assistant);
public slots:
    void addAnImageFile();
    void deleteAnItem();
    void clearAllItems();
    void showThumbnail();
private:
    QLabel *text_image;
    QComboBox *box_image;

    QFileDialog *filedialog;

    QStringList *file_name_list;

    QPushButton *button_add;
    QPushButton *button_delete;
    QPushButton *button_reset;

    QLabel *thumbnail;

    Assistant assistant;
};
#endif // IMAGESECTION_H

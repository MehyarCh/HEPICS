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

namespace Ui {
    class Image_Section;
}

class ImageSection : public QWidget
{
    Q_OBJECT
public:
    explicit ImageSection(QMainWindow *parent);
public slots:
    void addAnImageFile();
    void deleteAnItem();
    void showThumbnail();
private:
    QLabel *text_image;
    QComboBox *box_image;

    QFileDialog *filedialog;

    QPushButton *button_add;
    QPushButton *button_delete;
    QPushButton *button_reset;

    QLabel *thumbnail;
};
#endif // IMAGESECTION_H

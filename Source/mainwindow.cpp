/** METU CENG587 Project
  * Author: Necip Fazil Yildiran
  * */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QFileDialog>
#include<QDir>
#include<QMessageBox>

#include<iostream>
#include<climits>

#include<opencv2/core.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/photo.hpp>

#include"debevec/header/image_basic_func.hpp"
#include"debevec/header/debevec_recovery.hpp"
#include"reinhard/header/reinhard_tonemapping.hpp"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::clearImageList()
{
    // clear the list in GUI
    ui->imageList->clear();

    // clear the file full paths list
    imageFilePaths.clear();

    // clear the fields
    besLdrImages.clear();
}

// given full paths, clears the current list, extracts the image names and adds to the list
void MainWindow::updateImageList(QStringList imageFileFullPaths)
{
    clearImageList();

    if(imageFileFullPaths.empty())
        return;

    imageFilePaths = imageFileFullPaths;

    // extract the file names from full file path
    QStringList fileNameSuffixes = imageFilePaths;

    for(QStringList::iterator it = fileNameSuffixes.begin(); it != fileNameSuffixes.end(); it++)
    {
        QString & filePath = (*it);

        int indexOfSeperator = filePath.lastIndexOf(QDir::separator());
        filePath.remove(0, indexOfSeperator + 1);
    }

    // add the extracted file name suffixes to the list
    ui->imageList->addItems(fileNameSuffixes);
}

bool MainWindow::readBesLdrImages()
{
    if(this->imageFilePaths.empty())
    {
        return false;
    }
    else
    {
        // from QStringList to std::vector of std::string
        std::vector<std::string> filePaths;

        for(QStringList::iterator it = imageFilePaths.begin(); it != imageFilePaths.end(); it++)
        {
            filePaths.push_back((*it).toStdString());
        }

        // now, read the ldr images
        this->besLdrImages = readImages(filePaths);

        return true;
    }
}

void MainWindow::on_pushButton_clicked()
{
    QStringList filePaths;

    // open file dialog and let the user choose the files
    filePaths = QFileDialog::getOpenFileNames(
                this,
                tr("Open LDR images"),
                QString(),
                tr("Image Files (*.png *.jpg *.jpeg *.tiff)")
                );

    if(filePaths.isEmpty())
        return;

    // if some file is selected, update the image list
    updateImageList(filePaths);

    // read images
    this->readBesLdrImages();

    // suggest resize factor
    if(!besLdrImages.empty())
    {
        int suggestedResizeFactor =suggestResize(besLdrImages[0]);
        ui->resizeFactor->setValue(suggestedResizeFactor);
    }

    this->statusBar()->showMessage(tr("Info: LDR image files are loaded."));
}

void MainWindow::on_createHDR_clicked()
{
    if(besLdrImages.size() < 2)
    {
        QMessageBox::warning(this, "Insufficient Input for HDR Recovery", "Please use a bracketed exposure sequence contaning at least two images.",QMessageBox::Ok);
        this->statusBar()->showMessage(tr("Warning: Insufficient input for HDR image recovery"));
        return;
    }

    this->statusBar()->showMessage(tr("Info: Recovering HDR image from LDR images.."));
    QMessageBox::information(this, "HDR Recovery is Starting", "The recovery process is going to start. Notice that this process may take a while (~20sec)", QMessageBox::Ok);

    this->hdrImage = createHdrFromBracketedExposureSequence_Debevec
    (
        besLdrImages,
        (float)ui->smoothness->value(),     // smoothness lambda
        (float)ui->resizeFactor->value()    //resizingFactor
    );

    this->statusBar()->showMessage(tr("Info: HDR image is recovered from LDR images."));
    QMessageBox::information(this, "HDR Recovery is Successful!", "The recovery process is successful.", QMessageBox::Ok);
}


void MainWindow::on_saveHDR_clicked()
{
    if(this->hdrImage.empty())
    {
        this->statusBar()->showMessage(tr("Warning: Recover the HDR image before saving!"));
        QMessageBox::warning(this, "Failure while saving HDR image", "No HDR image file to be saved", QMessageBox::Ok);
        return;
    }

    QString saveFileName = QFileDialog::getSaveFileName(
                this,
                tr("Save HDR image"),
                QString(),
                tr("HDR Image (*.hdr *.exr)"));

    QString statusMsg;

    try
    {
        // write hdr image
        cv::imwrite(saveFileName.toStdString(), this->hdrImage);

        statusMsg = QString("Info: HDR image is saved to: ") + saveFileName;
    }
    catch(exception e)
    {
        statusMsg = QString("Error: HDR image could not be saved!");
        QMessageBox::warning(this, "Failure while saving HDR image", "Failure while saving HDR image: " + QString(e.what()), QMessageBox::Ok);
    }

    this->statusBar()->showMessage(statusMsg);

}

void MainWindow::on_viewTonemappedImage_clicked()
{
    if(this->toneMappedImage.empty())
    {
        this->statusBar()->showMessage(tr("Warning: Tonemap a HDR image to view the tonemapped image!"));
        QMessageBox::warning(this, "Failure while viewing tonemapped image", "No tonemapped image file to be viewed", QMessageBox::Ok);
        return;
    }

    std::string windowName = "Tonemapped Image";
    cv::namedWindow(windowName, cv::WINDOW_NORMAL);
    cv::imshow(windowName, quantizeImage(this->toneMappedImage));

    cv::waitKey(0);
}

void MainWindow::on_saveTonemappedImage_clicked()
{
    if(this->toneMappedImage.empty())
    {
        this->statusBar()->showMessage(tr("Warning: Tonemap a HDR image before saving the tonemapped image!"));
        QMessageBox::warning(this, "Failure while saving tonemapped image", "No tonampped image file to be saved", QMessageBox::Ok);
        return;
    }

    QString saveFileName = QFileDialog::getSaveFileName(
                this,
                tr("Save tonemapped image"),
                QString(),
                tr("Image (*.jpg *.jpeg *.png *.tiff)"));

    if(saveFileName.isEmpty())
        return;

    QString statusMsg;

    try
    {
        // quantize & save
        cv::imwrite(saveFileName.toStdString(), quantizeImage(toneMappedImage));

        // update status msg
        statusMsg = QString("Info: Tonemapped image is saved to: ") + saveFileName;
    }
    catch(exception e)
    {
        statusMsg = QString("Error: Tonemapped image could not be saved!");
        QMessageBox::warning(this, "Failure while saving tonemapped image", "Failure while saving tonemapped image: " + QString(e.what()), QMessageBox::Ok);
    }

    this->statusBar()->showMessage(statusMsg);
}

void MainWindow::on_lMaxCheckBox_stateChanged(int arg1)
{
    if(arg1 == 0)
    {
        ui->lMax->setValue(FLT_MAX);
        ui->lMax->setEnabled(false);
    }
    else
    {
        ui->lMax->setEnabled(true);
        ui->lMax->setValue(1000.0);
    }
}

void MainWindow::on_openHdrFile_clicked()
{
    // open file dialog and let the user choose the files
    QString hdrFilePath = QFileDialog::getOpenFileName(
                this,
                tr("Open HDR image"),
                QString(),
                tr("HDR Image File (*.exr *.hdr)")
                );

    // if no file is selected, just return
    if(hdrFilePath.isEmpty())
        return;

    // if some file is selected, update the hdr image
    this->hdrImage = cv::imread(hdrFilePath.toLatin1().data(), cv::IMREAD_UNCHANGED);

    this->statusBar()->showMessage(tr("Info: HDR image file is loaded from file."));
}

void MainWindow::on_tonemap_clicked()
{
    if(this->hdrImage.empty())
    {
        this->statusBar()->showMessage(tr("Warning: Insufficient input for tonemapping."));
        QMessageBox::warning(this, "Insufficient Input for Tonemapping", "Please load a HDR image or recover a HDR image to tonemap.",QMessageBox::Ok);
        return;
    }

    this->toneMappedImage = globalTMO(
                this->hdrImage,
                (float)ui->keyValueGlobal->value(),
                ui->lMax->value()
                );

    this->statusBar()->showMessage(tr("Info: Reinhard et al.'s global TMO is applied on HDR image."));
}

void MainWindow::on_localTonemap_clicked()
{
    if(this->hdrImage.empty())
    {
        this->statusBar()->showMessage(tr("Warning: Insufficient input for tonemapping."));
        QMessageBox::warning(this, "Insufficient Input for Tonemapping", "Please load a HDR image or recover a HDR image to tonemap.",QMessageBox::Ok);
        return;
    }

    this->toneMappedImage = localTMO(
                this->hdrImage,
                (float)ui->keyValueLocal->value(),
                (float)ui->sharpening->value(),
                (float)ui->threshold->value()
                //ui->lMax->value()
                );

    this->statusBar()->showMessage(tr("Info: Reinhard et al.'s local TMO is applied on HDR image."));
}

void MainWindow::removeFromLdrImageList(int index)
{
    if(index > (int)besLdrImages.size() || index > imageFilePaths.size())
        return;

    // from image list
    vector<cv::Mat>::iterator besLdrImageIt = besLdrImages.begin();
    this->besLdrImages.erase(besLdrImageIt + index);

    // from file path
    QStringList::iterator filePathIt = imageFilePaths.begin();
    imageFilePaths.erase(filePathIt + index);

}

void MainWindow::on_listX_clicked()
{
    if(ui->imageList->count() == 0 || ui->imageList->selectedItems().empty())
        return;

    QList<QListWidgetItem*> selected = ui->imageList->selectedItems();

    int selectedIndex = selected[0]->listWidget()->currentIndex().row();
    removeFromLdrImageList(selectedIndex);

    qDeleteAll(selected);
}

void MainWindow::on_listUp_clicked()
{
    if(ui->imageList->count() == 0 || ui->imageList->selectedItems().empty())
        return;

    QList<QListWidgetItem*> selected = ui->imageList->selectedItems();

    int selectedIndex = selected[0]->listWidget()->currentIndex().row();

    // if selected is the first item, return
    if(selectedIndex == 0)
        return;

    // swap in list view
    QListWidgetItem* item = ui->imageList->takeItem(selectedIndex);
    ui->imageList->insertItem(selectedIndex - 1, item);

    // swap in image list
    cv::Mat imageToUp = this->besLdrImages[selectedIndex];
    cv::Mat tempImage = this->besLdrImages[selectedIndex - 1];

    this->besLdrImages[selectedIndex - 1] = imageToUp;
    this->besLdrImages[selectedIndex] = tempImage;

    // swap in file path list
    QString filePathToUp = this->imageFilePaths[selectedIndex];
    QString tempFilePath = this->imageFilePaths[selectedIndex - 1];

    this->imageFilePaths[selectedIndex - 1] = filePathToUp;
    this->imageFilePaths[selectedIndex] = tempFilePath;

    // set the list's new selected item as the swapped item
    ui->imageList->clearSelection();
    ui->imageList->item(selectedIndex - 1)->setSelected(true);
    ui->imageList->setCurrentRow(selectedIndex - 1);
}

void MainWindow::on_listDown_clicked()
{
    if(ui->imageList->count() == 0 || ui->imageList->selectedItems().empty())
        return;

    QList<QListWidgetItem*> selected = ui->imageList->selectedItems();

    int selectedIndex = selected[0]->listWidget()->currentIndex().row();

    // if selected is the first item, return
    if(selectedIndex == ui->imageList->count() - 1)
        return;

    // swap in list view
    QListWidgetItem* item = ui->imageList->takeItem(selectedIndex);
    ui->imageList->insertItem(selectedIndex + 1, item);

    // swap in image list
    cv::Mat imageToUp = this->besLdrImages[selectedIndex];
    cv::Mat tempImage = this->besLdrImages[selectedIndex + 1];

    this->besLdrImages[selectedIndex + 1] = imageToUp;
    this->besLdrImages[selectedIndex] = tempImage;

    // swap in file path list
    QString filePathToUp = this->imageFilePaths[selectedIndex];
    QString tempFilePath = this->imageFilePaths[selectedIndex + 1];

    this->imageFilePaths[selectedIndex + 1] = filePathToUp;
    this->imageFilePaths[selectedIndex] = tempFilePath;

    // set the list's new selected item as the swapped item
    ui->imageList->clearSelection();
    ui->imageList->item(selectedIndex + 1)->setSelected(true);
    ui->imageList->setCurrentRow(selectedIndex + 1);
}

void MainWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include<vector>
#include<string>
#include<opencv2/core.hpp>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_pushButton_clicked();

    void on_createHDR_clicked();

    void on_saveHDR_clicked();

    void on_tonemap_clicked();

    void on_viewTonemappedImage_clicked();

    void on_saveTonemappedImage_clicked();

    void on_lMaxCheckBox_stateChanged(int arg1);

    void on_openHdrFile_clicked();

    void on_localTonemap_clicked();

    void on_listX_clicked();

    void removeFromLdrImageList(int index);

    void on_listUp_clicked();

    void on_listDown_clicked();

    void on_actionQuit_triggered();

private:
    Ui::MainWindow *ui;

    QStringList imageFilePaths;
    cv::Mat hdrImage;
    cv::Mat toneMappedImage;
    std::vector<cv::Mat> besLdrImages;

    void updateImageList(QStringList imageFileFullPaths);
    void clearImageList();
    bool readBesLdrImages();


};

#endif // MAINWINDOW_H

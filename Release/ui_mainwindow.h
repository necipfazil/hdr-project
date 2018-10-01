/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QFrame>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionQuit;
    QWidget *centralWidget;
    QGroupBox *ldrGroup;
    QPushButton *pushButton;
    QListWidget *imageList;
    QDoubleSpinBox *smoothness;
    QLabel *smoothnessLabel;
    QDoubleSpinBox *resizeFactor;
    QLabel *resizeFactorLabel;
    QPushButton *saveHDR;
    QPushButton *createHDR;
    QPushButton *listX;
    QPushButton *listUp;
    QPushButton *listDown;
    QFrame *line_2;
    QGroupBox *tmoGroup;
    QPushButton *tonemap;
    QPushButton *viewTonemappedImage;
    QPushButton *saveTonemappedImage;
    QLabel *keyValueLabel;
    QDoubleSpinBox *keyValueGlobal;
    QDoubleSpinBox *lMax;
    QCheckBox *lMaxCheckBox;
    QPushButton *openHdrFile;
    QPushButton *localTonemap;
    QDoubleSpinBox *sharpening;
    QLabel *sharpeningLabel;
    QDoubleSpinBox *threshold;
    QLabel *thresholdLabel;
    QFrame *line;
    QDoubleSpinBox *keyValueLocal;
    QLabel *keyValueLabel_2;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(733, 380);
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        QIcon icon;
        QString iconThemeName = QString::fromUtf8("Quit");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon = QIcon::fromTheme(iconThemeName);
        } else {
            icon.addFile(QString::fromUtf8("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        actionQuit->setIcon(icon);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        ldrGroup = new QGroupBox(centralWidget);
        ldrGroup->setObjectName(QString::fromUtf8("ldrGroup"));
        ldrGroup->setEnabled(true);
        ldrGroup->setGeometry(QRect(10, 10, 381, 321));
        ldrGroup->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    border: 1px solid gray;\n"
"    border-radius: 9px;\n"
"    margin-top: 0.5em;\n"
"}\n"
"\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    left: 15px;\n"
"    padding: 0 3px 0 3px;\n"
"}"));
        ldrGroup->setFlat(false);
        ldrGroup->setCheckable(false);
        pushButton = new QPushButton(ldrGroup);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(10, 270, 131, 41));
        imageList = new QListWidget(ldrGroup);
        imageList->setObjectName(QString::fromUtf8("imageList"));
        imageList->setGeometry(QRect(10, 30, 131, 231));
        imageList->setAutoFillBackground(false);
        imageList->setSelectionBehavior(QAbstractItemView::SelectRows);
        smoothness = new QDoubleSpinBox(ldrGroup);
        smoothness->setObjectName(QString::fromUtf8("smoothness"));
        smoothness->setGeometry(QRect(280, 80, 91, 21));
        smoothness->setMaximum(100000);
        smoothness->setSingleStep(1);
        smoothness->setValue(1);
        smoothnessLabel = new QLabel(ldrGroup);
        smoothnessLabel->setObjectName(QString::fromUtf8("smoothnessLabel"));
        smoothnessLabel->setGeometry(QRect(200, 80, 71, 21));
        resizeFactor = new QDoubleSpinBox(ldrGroup);
        resizeFactor->setObjectName(QString::fromUtf8("resizeFactor"));
        resizeFactor->setGeometry(QRect(280, 110, 91, 21));
        resizeFactor->setDecimals(2);
        resizeFactor->setMinimum(1);
        resizeFactor->setMaximum(1000);
        resizeFactor->setSingleStep(1);
        resizeFactor->setValue(1);
        resizeFactorLabel = new QLabel(ldrGroup);
        resizeFactorLabel->setObjectName(QString::fromUtf8("resizeFactorLabel"));
        resizeFactorLabel->setGeometry(QRect(200, 110, 71, 21));
        saveHDR = new QPushButton(ldrGroup);
        saveHDR->setObjectName(QString::fromUtf8("saveHDR"));
        saveHDR->setEnabled(true);
        saveHDR->setGeometry(QRect(200, 200, 171, 41));
        createHDR = new QPushButton(ldrGroup);
        createHDR->setObjectName(QString::fromUtf8("createHDR"));
        createHDR->setEnabled(true);
        createHDR->setGeometry(QRect(200, 150, 171, 41));
        listX = new QPushButton(ldrGroup);
        listX->setObjectName(QString::fromUtf8("listX"));
        listX->setGeometry(QRect(150, 130, 21, 31));
        QFont font;
        font.setPointSize(15);
        font.setBold(true);
        font.setWeight(75);
        listX->setFont(font);
        listUp = new QPushButton(ldrGroup);
        listUp->setObjectName(QString::fromUtf8("listUp"));
        listUp->setGeometry(QRect(150, 80, 21, 41));
        listUp->setFont(font);
        listDown = new QPushButton(ldrGroup);
        listDown->setObjectName(QString::fromUtf8("listDown"));
        listDown->setGeometry(QRect(150, 170, 21, 41));
        QFont font1;
        font1.setPointSize(18);
        font1.setBold(true);
        font1.setWeight(75);
        font1.setStrikeOut(false);
        font1.setKerning(true);
        listDown->setFont(font1);
        line_2 = new QFrame(ldrGroup);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setGeometry(QRect(180, 30, 20, 261));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);
        pushButton->raise();
        imageList->raise();
        smoothness->raise();
        smoothnessLabel->raise();
        resizeFactor->raise();
        resizeFactorLabel->raise();
        saveHDR->raise();
        createHDR->raise();
        listUp->raise();
        listDown->raise();
        listX->raise();
        line_2->raise();
        tmoGroup = new QGroupBox(centralWidget);
        tmoGroup->setObjectName(QString::fromUtf8("tmoGroup"));
        tmoGroup->setEnabled(true);
        tmoGroup->setGeometry(QRect(400, 10, 321, 321));
        tmoGroup->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    border: 1px solid gray;\n"
"    border-radius: 9px;\n"
"    margin-top: 0.5em;\n"
"}\n"
"\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    left: 15px;\n"
"    padding: 0 3px 0 3px;\n"
"}"));
        tonemap = new QPushButton(tmoGroup);
        tonemap->setObjectName(QString::fromUtf8("tonemap"));
        tonemap->setEnabled(true);
        tonemap->setGeometry(QRect(10, 160, 141, 41));
        viewTonemappedImage = new QPushButton(tmoGroup);
        viewTonemappedImage->setObjectName(QString::fromUtf8("viewTonemappedImage"));
        viewTonemappedImage->setEnabled(true);
        viewTonemappedImage->setGeometry(QRect(10, 220, 301, 41));
        saveTonemappedImage = new QPushButton(tmoGroup);
        saveTonemappedImage->setObjectName(QString::fromUtf8("saveTonemappedImage"));
        saveTonemappedImage->setEnabled(true);
        saveTonemappedImage->setGeometry(QRect(10, 270, 301, 41));
        keyValueLabel = new QLabel(tmoGroup);
        keyValueLabel->setObjectName(QString::fromUtf8("keyValueLabel"));
        keyValueLabel->setGeometry(QRect(10, 80, 61, 21));
        keyValueGlobal = new QDoubleSpinBox(tmoGroup);
        keyValueGlobal->setObjectName(QString::fromUtf8("keyValueGlobal"));
        keyValueGlobal->setGeometry(QRect(80, 80, 71, 21));
        keyValueGlobal->setDecimals(4);
        keyValueGlobal->setMinimum(-999999);
        keyValueGlobal->setMaximum(999.99);
        keyValueGlobal->setSingleStep(0.01);
        keyValueGlobal->setValue(0.18);
        lMax = new QDoubleSpinBox(tmoGroup);
        lMax->setObjectName(QString::fromUtf8("lMax"));
        lMax->setEnabled(false);
        lMax->setGeometry(QRect(80, 120, 71, 21));
        lMax->setDecimals(1);
        lMax->setMaximum(3.40282e+44);
        lMax->setSingleStep(0.01);
        lMax->setValue(3.40282e+44);
        lMaxCheckBox = new QCheckBox(tmoGroup);
        lMaxCheckBox->setObjectName(QString::fromUtf8("lMaxCheckBox"));
        lMaxCheckBox->setGeometry(QRect(10, 120, 69, 20));
        openHdrFile = new QPushButton(tmoGroup);
        openHdrFile->setObjectName(QString::fromUtf8("openHdrFile"));
        openHdrFile->setEnabled(true);
        openHdrFile->setGeometry(QRect(10, 20, 301, 41));
        localTonemap = new QPushButton(tmoGroup);
        localTonemap->setObjectName(QString::fromUtf8("localTonemap"));
        localTonemap->setEnabled(true);
        localTonemap->setGeometry(QRect(170, 160, 141, 41));
        sharpening = new QDoubleSpinBox(tmoGroup);
        sharpening->setObjectName(QString::fromUtf8("sharpening"));
        sharpening->setGeometry(QRect(240, 100, 71, 21));
        sharpening->setDecimals(4);
        sharpening->setMinimum(-999999);
        sharpening->setMaximum(999.99);
        sharpening->setSingleStep(0.1);
        sharpening->setValue(8);
        sharpeningLabel = new QLabel(tmoGroup);
        sharpeningLabel->setObjectName(QString::fromUtf8("sharpeningLabel"));
        sharpeningLabel->setGeometry(QRect(170, 100, 71, 21));
        threshold = new QDoubleSpinBox(tmoGroup);
        threshold->setObjectName(QString::fromUtf8("threshold"));
        threshold->setGeometry(QRect(240, 130, 71, 21));
        threshold->setDecimals(4);
        threshold->setMinimum(-999999);
        threshold->setMaximum(999.99);
        threshold->setSingleStep(0.001);
        threshold->setValue(0.005);
        thresholdLabel = new QLabel(tmoGroup);
        thresholdLabel->setObjectName(QString::fromUtf8("thresholdLabel"));
        thresholdLabel->setGeometry(QRect(170, 130, 61, 21));
        line = new QFrame(tmoGroup);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(150, 80, 20, 121));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        keyValueLocal = new QDoubleSpinBox(tmoGroup);
        keyValueLocal->setObjectName(QString::fromUtf8("keyValueLocal"));
        keyValueLocal->setGeometry(QRect(240, 70, 71, 21));
        keyValueLocal->setDecimals(4);
        keyValueLocal->setMinimum(-999999);
        keyValueLocal->setMaximum(999.99);
        keyValueLocal->setSingleStep(0.01);
        keyValueLocal->setValue(0.18);
        keyValueLabel_2 = new QLabel(tmoGroup);
        keyValueLabel_2->setObjectName(QString::fromUtf8("keyValueLabel_2"));
        keyValueLabel_2->setGeometry(QRect(170, 70, 61, 21));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 733, 19));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addSeparator();
        menuFile->addAction(actionQuit);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "nfyHDR", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        MainWindow->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
        actionQuit->setText(QApplication::translate("MainWindow", "Quit", 0, QApplication::UnicodeUTF8));
        ldrGroup->setTitle(QApplication::translate("MainWindow", "HDRI Recovery", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("MainWindow", "Open Image Files", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        imageList->setToolTip(QApplication::translate("MainWindow", "Input LDR images to be used while HDR recovery. The items should be ordered in exposure time ascending order.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        imageList->setWhatsThis(QString());
#endif // QT_NO_WHATSTHIS
#ifndef QT_NO_TOOLTIP
        smoothness->setToolTip(QApplication::translate("MainWindow", "Smoothness value to be used while recovering the response curve of the camera that the input LDR images are photographed.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        smoothnessLabel->setToolTip(QApplication::translate("MainWindow", "Smoothness value to be used while recovering the response curve of the camera that the input LDR images are photographed.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        smoothnessLabel->setText(QApplication::translate("MainWindow", "  Smoothness:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        resizeFactor->setToolTip(QApplication::translate("MainWindow", "Resize factor that will be used while downsampling the input LDR images to speed up the HDR recovery process. An initial value will be suggested when the images are loaded.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        resizeFactorLabel->setToolTip(QApplication::translate("MainWindow", "Resize factor that will be used while downsampling the input LDR images to speed up the HDR recovery process. An initial value will be suggested when the images are loaded.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        resizeFactorLabel->setWhatsThis(QString());
#endif // QT_NO_WHATSTHIS
        resizeFactorLabel->setText(QApplication::translate("MainWindow", "Resize Factor:", 0, QApplication::UnicodeUTF8));
        saveHDR->setText(QApplication::translate("MainWindow", "Save HDR", 0, QApplication::UnicodeUTF8));
        createHDR->setText(QApplication::translate("MainWindow", "Recover HDR", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        listX->setToolTip(QApplication::translate("MainWindow", "Remove the selected image from image list", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        listX->setText(QApplication::translate("MainWindow", "X", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        listUp->setToolTip(QApplication::translate("MainWindow", "Move the selected image up", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        listUp->setText(QApplication::translate("MainWindow", "\312\214", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        listDown->setToolTip(QApplication::translate("MainWindow", "Move the selected image down", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        listDown->setText(QApplication::translate("MainWindow", "v", 0, QApplication::UnicodeUTF8));
        tmoGroup->setTitle(QApplication::translate("MainWindow", "Tonemapping", 0, QApplication::UnicodeUTF8));
        tonemap->setText(QApplication::translate("MainWindow", "Global\n"
"Tonemapping", 0, QApplication::UnicodeUTF8));
        viewTonemappedImage->setText(QApplication::translate("MainWindow", "View Tonemapped Image", 0, QApplication::UnicodeUTF8));
        saveTonemappedImage->setText(QApplication::translate("MainWindow", "Save Tonemapped Image", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        keyValueLabel->setToolTip(QApplication::translate("MainWindow", "Key value that is going to be used while tonemapping the input HDR image.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        keyValueLabel->setText(QApplication::translate("MainWindow", "Key Value:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        keyValueGlobal->setToolTip(QApplication::translate("MainWindow", "Key value that is going to be used while tonemapping the input HDR image.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        lMax->setToolTip(QApplication::translate("MainWindow", "The luminosity value that controls where the burning starts in output tonemapped LDR image.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        lMaxCheckBox->setToolTip(QApplication::translate("MainWindow", "The luminosity value that controls where the burning starts in output tonemapped LDR image.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        lMaxCheckBox->setText(QApplication::translate("MainWindow", "Lmax", 0, QApplication::UnicodeUTF8));
        openHdrFile->setText(QApplication::translate("MainWindow", "Open HDR Image File", 0, QApplication::UnicodeUTF8));
        localTonemap->setText(QApplication::translate("MainWindow", "Local\n"
"Tonemapping", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        sharpening->setToolTip(QApplication::translate("MainWindow", "Sharpening value that controls the sharpness of edges while applying local tonemapping method.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        sharpeningLabel->setToolTip(QApplication::translate("MainWindow", "Sharpening value that controls the sharpness of edges while applying local tonemapping method.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        sharpeningLabel->setText(QApplication::translate("MainWindow", "Sharpening:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        threshold->setToolTip(QApplication::translate("MainWindow", "Threshold to be used while determining the local average luminosity of each pixel while applying local tonemapping method.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        thresholdLabel->setToolTip(QApplication::translate("MainWindow", "Threshold to be used while determining the local average luminosity of each pixel while applying local tonemapping method.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        thresholdLabel->setText(QApplication::translate("MainWindow", "Threshold:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        keyValueLocal->setToolTip(QApplication::translate("MainWindow", "Key value that is going to be used while tonemapping the input HDR image.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        keyValueLabel_2->setToolTip(QApplication::translate("MainWindow", "Key value that is going to be used while tonemapping the input HDR image.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        keyValueLabel_2->setText(QApplication::translate("MainWindow", "Key Value:", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

/********************************************************************************
** Form generated from reading UI file 'notepad_mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.1.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NOTEPAD_MAINWINDOW_H
#define UI_NOTEPAD_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Notepad_MainWindow
{
public:
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionSave_As;
    QAction *actionPrint;
    QAction *actionExist;
    QAction *actionCopy;
    QAction *actionCut;
    QAction *actionPaste;
    QAction *actionUndo;
    QAction *actionRedo;
    QAction *actionSave;
    QAction *actionConvert_to_jason;
    QAction *actionDetect_Errors;
    QAction *actionFix;
    QAction *actionMinfy;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QPlainTextEdit *plainTextEdit1;
    QTextEdit *textEdit_errors;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuActions;
    QToolBar *toolBar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Notepad_MainWindow)
    {
        if (Notepad_MainWindow->objectName().isEmpty())
            Notepad_MainWindow->setObjectName(QString::fromUtf8("Notepad_MainWindow"));
        Notepad_MainWindow->resize(739, 583);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Notepad_MainWindow->sizePolicy().hasHeightForWidth());
        Notepad_MainWindow->setSizePolicy(sizePolicy);
        actionNew = new QAction(Notepad_MainWindow);
        actionNew->setObjectName(QString::fromUtf8("actionNew"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/add-file.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNew->setIcon(icon);
        actionOpen = new QAction(Notepad_MainWindow);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/Icons/google/2x/outline_open_in_new_black_24dp.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen->setIcon(icon1);
        actionSave_As = new QAction(Notepad_MainWindow);
        actionSave_As->setObjectName(QString::fromUtf8("actionSave_As"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/Icons/google/2x/outline_save_black_24dp.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave_As->setIcon(icon2);
        actionPrint = new QAction(Notepad_MainWindow);
        actionPrint->setObjectName(QString::fromUtf8("actionPrint"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/images/Icons/icons8-print-50.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPrint->setIcon(icon3);
        actionExist = new QAction(Notepad_MainWindow);
        actionExist->setObjectName(QString::fromUtf8("actionExist"));
        actionCopy = new QAction(Notepad_MainWindow);
        actionCopy->setObjectName(QString::fromUtf8("actionCopy"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/images/Icons/google/2x/outline_content_copy_black_24dp.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCopy->setIcon(icon4);
        actionCut = new QAction(Notepad_MainWindow);
        actionCut->setObjectName(QString::fromUtf8("actionCut"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/images/Icons/google/2x/outline_content_cut_black_24dp.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCut->setIcon(icon5);
        actionPaste = new QAction(Notepad_MainWindow);
        actionPaste->setObjectName(QString::fromUtf8("actionPaste"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/images/paste-131964784935783245_256.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionPaste->setIcon(icon6);
        actionUndo = new QAction(Notepad_MainWindow);
        actionUndo->setObjectName(QString::fromUtf8("actionUndo"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/images/Icons/undo-1325051879300270680_256.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionUndo->setIcon(icon7);
        actionRedo = new QAction(Notepad_MainWindow);
        actionRedo->setObjectName(QString::fromUtf8("actionRedo"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/images/Icons/redo-1324760616182504055_256.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionRedo->setIcon(icon8);
        actionSave = new QAction(Notepad_MainWindow);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        actionSave->setIcon(icon2);
        actionConvert_to_jason = new QAction(Notepad_MainWindow);
        actionConvert_to_jason->setObjectName(QString::fromUtf8("actionConvert_to_jason"));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/images/Icons/Jason.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionConvert_to_jason->setIcon(icon9);
        actionDetect_Errors = new QAction(Notepad_MainWindow);
        actionDetect_Errors->setObjectName(QString::fromUtf8("actionDetect_Errors"));
        actionFix = new QAction(Notepad_MainWindow);
        actionFix->setObjectName(QString::fromUtf8("actionFix"));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/images/Icons/icon-hammer-10.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        actionFix->setIcon(icon10);
        actionMinfy = new QAction(Notepad_MainWindow);
        actionMinfy->setObjectName(QString::fromUtf8("actionMinfy"));
        centralwidget = new QWidget(Notepad_MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        plainTextEdit1 = new QPlainTextEdit(centralwidget);
        plainTextEdit1->setObjectName(QString::fromUtf8("plainTextEdit1"));
        plainTextEdit1->setMinimumSize(QSize(720, 0));

        verticalLayout->addWidget(plainTextEdit1);

        textEdit_errors = new QTextEdit(centralwidget);
        textEdit_errors->setObjectName(QString::fromUtf8("textEdit_errors"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(textEdit_errors->sizePolicy().hasHeightForWidth());
        textEdit_errors->setSizePolicy(sizePolicy1);
        textEdit_errors->setMinimumSize(QSize(720, 100));
        textEdit_errors->setMaximumSize(QSize(3840, 100));
        textEdit_errors->setAcceptDrops(false);
        textEdit_errors->setReadOnly(true);

        verticalLayout->addWidget(textEdit_errors);

        Notepad_MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Notepad_MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 739, 20));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuEdit = new QMenu(menubar);
        menuEdit->setObjectName(QString::fromUtf8("menuEdit"));
        menuActions = new QMenu(menubar);
        menuActions->setObjectName(QString::fromUtf8("menuActions"));
        Notepad_MainWindow->setMenuBar(menubar);
        toolBar = new QToolBar(Notepad_MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        Notepad_MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);
        statusbar = new QStatusBar(Notepad_MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        Notepad_MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuEdit->menuAction());
        menubar->addAction(menuActions->menuAction());
        menuFile->addAction(actionNew);
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave);
        menuFile->addAction(actionSave_As);
        menuFile->addAction(actionPrint);
        menuFile->addAction(actionExist);
        menuEdit->addAction(actionCopy);
        menuEdit->addAction(actionPaste);
        menuEdit->addAction(actionCut);
        menuEdit->addAction(actionUndo);
        menuEdit->addAction(actionRedo);
        menuActions->addAction(actionDetect_Errors);
        menuActions->addAction(actionFix);
        menuActions->addAction(actionMinfy);
        menuActions->addAction(actionConvert_to_jason);
        toolBar->addSeparator();
        toolBar->addAction(actionDetect_Errors);
        toolBar->addAction(actionFix);
        toolBar->addAction(actionMinfy);
        toolBar->addAction(actionConvert_to_jason);

        retranslateUi(Notepad_MainWindow);

        QMetaObject::connectSlotsByName(Notepad_MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *Notepad_MainWindow)
    {
        Notepad_MainWindow->setWindowTitle(QCoreApplication::translate("Notepad_MainWindow", "Notepad_MainWindow", nullptr));
        actionNew->setText(QCoreApplication::translate("Notepad_MainWindow", "New", nullptr));
        actionOpen->setText(QCoreApplication::translate("Notepad_MainWindow", "Open", nullptr));
        actionSave_As->setText(QCoreApplication::translate("Notepad_MainWindow", "Save as", nullptr));
        actionPrint->setText(QCoreApplication::translate("Notepad_MainWindow", "Print", nullptr));
        actionExist->setText(QCoreApplication::translate("Notepad_MainWindow", "Exist", nullptr));
        actionCopy->setText(QCoreApplication::translate("Notepad_MainWindow", "Copy", nullptr));
        actionCut->setText(QCoreApplication::translate("Notepad_MainWindow", "Cut", nullptr));
        actionPaste->setText(QCoreApplication::translate("Notepad_MainWindow", "Paste", nullptr));
        actionUndo->setText(QCoreApplication::translate("Notepad_MainWindow", "Undo", nullptr));
        actionRedo->setText(QCoreApplication::translate("Notepad_MainWindow", "Redo", nullptr));
        actionSave->setText(QCoreApplication::translate("Notepad_MainWindow", "Save", nullptr));
        actionConvert_to_jason->setText(QCoreApplication::translate("Notepad_MainWindow", "Convert to .jason", nullptr));
        actionDetect_Errors->setText(QCoreApplication::translate("Notepad_MainWindow", "Detect Errors", nullptr));
        actionFix->setText(QCoreApplication::translate("Notepad_MainWindow", "Fix", nullptr));
        actionMinfy->setText(QCoreApplication::translate("Notepad_MainWindow", "Minfy", nullptr));
        menuFile->setTitle(QCoreApplication::translate("Notepad_MainWindow", "File", nullptr));
        menuEdit->setTitle(QCoreApplication::translate("Notepad_MainWindow", "Edit", nullptr));
        menuActions->setTitle(QCoreApplication::translate("Notepad_MainWindow", "Actions", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("Notepad_MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Notepad_MainWindow: public Ui_Notepad_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NOTEPAD_MAINWINDOW_H

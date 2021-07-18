#ifndef NOTEPAD_MAINWINDOW_H
#define NOTEPAD_MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QPrinter>
#include <QPrintDialog>

#include <QLabel>

#include "XMLfunctions.h"
#include "correction.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Notepad_MainWindow; }
QT_END_NAMESPACE

class Notepad_MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    Notepad_MainWindow(QWidget *parent = nullptr);
    ~Notepad_MainWindow();

private slots:

    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_As_triggered();

    void on_actionSave_triggered();

    void on_actionPrint_triggered();

    void on_actionExit_triggered();

    void on_actionCopy_triggered();

    void on_actionCut_triggered();

    void on_actionPaste_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_actionDetect_Errors_triggered();

    void on_actionFix_triggered();

    void on_plainTextEdit1_cursorPositionChanged();

    void on_actionConvert_to_jason_triggered();

    void on_actionMinfy_triggered();

private:
    Ui::Notepad_MainWindow *ui;
    QString CurrentFile="";
    std::vector<Tag> errors;
    //used for curser position info
    QLabel * Label; /** Use the QLabel object to show info */
    QTextCursor* CurserInfo;
    //end used for curser position info

};
#endif // NOTEPAD_MAINWINDOW_H

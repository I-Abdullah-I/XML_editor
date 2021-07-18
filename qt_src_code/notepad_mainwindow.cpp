#include "notepad_mainwindow.h"
#include "ui_notepad_mainwindow.h"


Notepad_MainWindow::Notepad_MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Notepad_MainWindow)
{
    ui->setupUi(this);
//    this->setCentralWidget(ui->plainTextEdit1);  // saying that this widget will take all of the screen
   // font configration
    QFont font;
    font.setFamily("Courier");
    font.setStyleHint(QFont::Monospace);
    font.setFixedPitch(true);
    font.setPointSize(10);
    ui->plainTextEdit1->setFont(font);
    ui->plainTextEdit1->setWordWrapMode(QTextOption::NoWrap);
   //end font configrtaion

    //CurserInfo position configration
     Label = new QLabel(this);  //defined in .h
     ui->statusbar->addWidget(Label);
     CurserInfo =new QTextCursor();
     *CurserInfo =  ui->plainTextEdit1->textCursor();//cursorForPosition();
     // call the event for first time to initialize the statusbar
     on_plainTextEdit1_cursorPositionChanged();
     //end handels Curser position
}

Notepad_MainWindow::~Notepad_MainWindow()
{
    delete ui;
}


//menu bar
void Notepad_MainWindow::on_actionNew_triggered()
{
    // Global referencing the current file that we are clearing
        CurrentFile.clear();
    // Clear the plainTextEdit1 widget buffer
        ui->plainTextEdit1->setPlainText(QString());
}

void Notepad_MainWindow::on_actionOpen_triggered()
{
    // Opens a dialog that allows you to select a file to open
    QString fileName = QFileDialog::getOpenFileName(this, "Open the file");

    // An object for reading and writing files
    QFile file(fileName);

    // Store the currentFile name
    CurrentFile = fileName;

    // Try to open the file as a read only file if possible or display a
    // warning dialog box
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;
    }

    // Set the title for the window to the file name
    setWindowTitle(fileName);

    // Interface for reading text
    QTextStream in(&file);

    // Copy text in the string
    QString text = in.readAll();

    // Put the text in the plainTextEdit1 widget
    ui->plainTextEdit1->setPlainText(text);

    // Close the file
    file.close();

    //reset the log file
    ui->textEdit_errors->setPlainText(QString());
}

void Notepad_MainWindow::on_actionSave_As_triggered()
{
    // Opens a dialog for saving a file
    QString fileName = QFileDialog::getSaveFileName(this, "Save as");

    // An object for reading and writing files
    QFile file(fileName);

    // Try to open a file with write only options
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }

    // Store the currentFile name
    CurrentFile = fileName;

    // Set the title for the window to the file name
    setWindowTitle(fileName);

    // Interface for writing text
    QTextStream out(&file);

    // Copy text in the plainTextEdit1 widget and convert to plain text
    QString text = ui->plainTextEdit1->toPlainText();

    // Output to file
    out << text;

    // Close the file
    file.close();
}

void Notepad_MainWindow::on_actionSave_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save");
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }
    CurrentFile = fileName;
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = ui->plainTextEdit1->toPlainText();
    out << text;
    file.close();
}

void Notepad_MainWindow::on_actionPrint_triggered()
{
    // Allows for interacting with printer
    QPrinter printer;

    // You'll put your printer name here
    printer.setPrinterName("Printer Name");

    // Create the print dialog and pass the name and parent
    QPrintDialog pDialog(&printer, this);

    if(pDialog.exec() == QDialog::Rejected){
        QMessageBox::warning(this, "Warning", "Cannot Access Printer");
        return;
    }

    // Send the text to the printer
    ui->plainTextEdit1->print(&printer);

}

void Notepad_MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void Notepad_MainWindow::on_actionCopy_triggered()
{
    ui->plainTextEdit1->copy();
}

void Notepad_MainWindow::on_actionCut_triggered()
{
    ui->plainTextEdit1->cut();
}

void Notepad_MainWindow::on_actionPaste_triggered()
{
    ui->plainTextEdit1->paste();
}

void Notepad_MainWindow::on_actionUndo_triggered()
{
    ui->plainTextEdit1->undo();
}

void Notepad_MainWindow::on_actionRedo_triggered()
{
    ui->plainTextEdit1->redo();
}

void Notepad_MainWindow::on_actionDetect_Errors_triggered()
{
    check_for_errors(CurrentFile.toStdString(),errors);
   for(int i=0;i<errors.size();i++){
    ui->textEdit_errors->append( QString::fromStdString(errors[i].tag)+" "+
            QString::fromStdString(errors[i].error_type)+"\n"+
            "Needs to be closed before row: "+QString::number(errors[i].c_row)+
                                ", colum: "+QString::number(errors[i].c_col));
    }
}

void Notepad_MainWindow::on_actionFix_triggered()
{
    QString NewString= QString ::fromStdString(fix_and_save(CurrentFile.toStdString()));
    ui->plainTextEdit1->setPlainText(NewString);
//    CurrentFile="prettified.xml"
}
//highlightig
//line numbring

void Notepad_MainWindow::on_plainTextEdit1_cursorPositionChanged()
{

    /** Update the info text */
    QString info="Row: "+QString::number(CurserInfo->blockNumber())+
            "   Line: "+QString::number(CurserInfo->positionInBlock())+
                "   Position: "+ QString::number(CurserInfo->position());
    Label->setText(info);
}


void Notepad_MainWindow::on_actionConvert_to_jason_triggered()
{
    string *jason_text=convert2jason("minified.xml");
    string text=*jason_text;
 ui->plainTextEdit1->setPlainText(QString::fromStdString(text));
 ui->textEdit_errors->setPlainText(QString());
}


void Notepad_MainWindow::on_actionMinfy_triggered()
{
    minify(CurrentFile.toStdString());
}


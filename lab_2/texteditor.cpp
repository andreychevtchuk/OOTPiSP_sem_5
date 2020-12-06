#include "texteditor.h"
#include "ui_texteditor.h"
#include <QtDebug>

TextEditor::TextEditor(const QString &fileName, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TextEditor)
{
    ui->setupUi(this);

    QSettings settings;
    ui->textEdit->setFont(
    settings.value("viewFont", QApplication::font()).value<QFont>());

    this->setAttribute(Qt::WA_DeleteOnClose);//Указывает Qt удалить этот виджет, когда он получает сообщение о закрытии

    setWindowTitle("TextEditor[*]");

    connect(ui->textEdit, SIGNAL(textChanged()), this, SLOT(documentModified()));
    connect(ui->textEdit, SIGNAL(copyAvailable(bool)), ui->actionCopy, SLOT(setEnabled(bool)));
    connect(ui->textEdit, SIGNAL(copyAvailable(bool)), ui->actionCut, SLOT(setEnabled(bool)));
    connect(ui->textEdit, SIGNAL(undoAvailable(bool)), ui->actionUndo, SLOT(setEnabled(bool)));
    connect(ui->textEdit, SIGNAL(redoAvailable(bool)), ui->actionRedo, SLOT(setEnabled(bool)));

    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(saveFile()));
    connect(ui->actionSaveAs, SIGNAL(triggered()), this, SLOT(saveFileAs()));

    loadFile(fileName);
}

TextEditor::~TextEditor()
{
    delete ui;
}

void TextEditor::closeEvent(QCloseEvent *e)
{
     if (isWindowModified())
        {
            switch(QMessageBox::warning(this, "Document was modified",
                                        "The document was modified. Do you want save your changes",
                                        QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel,
                                        QMessageBox::Yes))
            {
            case QMessageBox::Yes:
                saveFile();
                e->ignore();
                break;
            case QMessageBox::No:
                e->accept();
                break;
            case QMessageBox::Cancel:
                e->ignore();
                break;
            }
        }
        else
        {
            e->accept();
        }

}


void TextEditor::on_actionNew_triggered()
{
    TextEditor *obj = new TextEditor;
    obj->show();
}

void TextEditor::on_actionClose_triggered()
{
    this->close();
}

void TextEditor::on_actionExit_triggered()
{
    qApp->closeAllWindows();
}

void TextEditor::documentModified()
{
    setWindowModified(true);
}

void TextEditor::on_actionSelectFont_triggered()
{
    bool ok;
      font = QFontDialog::getFont(&ok, this);

      if (ok) {
          QSettings settings;
          settings.setValue("viewFont", font);
          ui->textEdit->setFont(font);
        } else return;
}

void TextEditor::on_actionAboutQt_triggered()
{
    qApp->aboutQt();
}

void TextEditor::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void TextEditor::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void TextEditor::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void TextEditor::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void TextEditor::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

void TextEditor::on_actionAbout_triggered()
{
    QMessageBox::about(this, tr("About program"),
                       tr("Important information about program"));
}

void TextEditor::loadFile(const QString &fileName)
{
    if(fileName.isNull() || fileName.isEmpty())
            setFileName(QString());
        else
        {
            QFile file(fileName);
            if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                QMessageBox::warning(this,
                                     "Can't open file",
                                     "This file can't be opened for reading");
                setFileName(QString());
                return;
            }
            QTextStream stream(&file);
            ui->textEdit->setText(stream.readAll());
            file.close();
            setFileName(fileName);
            setWindowModified(false);
    }
}

void TextEditor::setFileName(const QString &fileName)
{
    this->fileName = fileName;
        setWindowTitle(QString("%1[*] - %2")
                       .arg(fileName.isNull()?"untitled":QFileInfo(fileName).fileName())
                       .arg(QApplication::applicationName()));
}

void TextEditor::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
         "Open document", QDir::currentPath(), "Text documents (*.txt *.cpp *.h *.xml)");

        if(fileName.isNull())
            return;

        if((this->fileName.isEmpty() || this->fileName.isNull()) && !isWindowModified())
            loadFile(fileName);
        else
        {
            TextEditor *newEditor = new TextEditor(fileName, this);
            newEditor->show();
        }
}

bool TextEditor::saveFile()
{
    if(this->fileName.isNull())
            return saveFileAs();
        else
        {
            QFile file(this->fileName);
            if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                QMessageBox::warning(this,
                                     "Can't save file",
                                     "This file can't be saved");
                setFileName(QString());
                return false;
            }

            QTextStream stream(&file);
            stream << ui->textEdit->toPlainText();
            file.close();
            setWindowModified(false);
            return true;
        }
}

bool TextEditor::saveFileAs()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save document",
                                                        this->fileName.isNull()?QDir::currentPath():this->fileName,
                                                        "Text documents (*.txt)");
        if(fileName.isNull())
            return false;
        else
        {
            setFileName(fileName);
            return saveFile();
        }
}

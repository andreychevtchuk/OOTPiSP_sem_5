#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <QMainWindow>
#include <QMessageBox>
#include <QCloseEvent>
#include <QFontDialog>
#include <QSettings>
#include <QString>
#include <QFileInfo>
#include <QFileDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class TextEditor; }
QT_END_NAMESPACE

class TextEditor : public QMainWindow
{
    Q_OBJECT

public:
    TextEditor(const QString &fileName=QString(), QWidget *parent = nullptr);
    ~TextEditor();

protected:
    void closeEvent(QCloseEvent *e);

private slots:
    void on_actionNew_triggered();

    void on_actionClose_triggered();

    void on_actionExit_triggered();

    void documentModified();

    void on_actionSelectFont_triggered();

    void on_actionAboutQt_triggered();

    void on_actionCut_triggered();

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_actionAbout_triggered();

    void on_actionOpen_triggered();

    bool saveFile();

    bool saveFileAs();

private:
    Ui::TextEditor *ui;
    QFont font;
    void loadFile(const QString &fileName);
    void setFileName(const QString &fileName);
    QString fileName;
};
#endif // TEXTEDITOR_H

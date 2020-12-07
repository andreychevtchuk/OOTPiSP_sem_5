#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <math.h>
#include <QShortcut>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    double pi = 3.141592653589793238462643;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_sinButton_clicked();

    void on_cosButton_clicked();

    void on_tgButton_clicked();


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

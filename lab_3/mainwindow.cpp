#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    ui->tableWidget->setRowCount(20);
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setColumnWidth(0, 120);
    ui->tableWidget->setColumnWidth(1, 130);
    ui->tableWidget->setColumnWidth(2, 120);
    ui->tableWidget->verticalHeader()->hide();
    ui->tableWidget->horizontalHeader()->hide();

    ui->tableWidget->setItem(0, 0, new QTableWidgetItem("Угол в градусах"));
    ui->tableWidget->setItem(0, 1, new QTableWidgetItem("Угол в радианах"));
    ui->tableWidget->setItem(0, 2, new QTableWidgetItem("Результат"));
    ui->tableWidget->item(0,0)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget->item(0,1)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget->item(0,2)->setTextAlignment(Qt::AlignCenter);

    QShortcut* keySin = new QShortcut(this);
    keySin->setKey(Qt:: CTRL + Qt::Key_S);
    connect(keySin, SIGNAL(activated()), this, SLOT(on_sinButton_clicked()));

    QShortcut* keyCos = new QShortcut(this);
    keyCos->setKey(Qt:: CTRL + Qt::Key_C);
    connect(keyCos, SIGNAL(activated()), this, SLOT(on_cosButton_clicked()));

    QShortcut* keyTg = new QShortcut(this);
    keyTg->setKey(Qt:: CTRL + Qt::Key_T);
    connect(keyTg, SIGNAL(activated()), this, SLOT(on_tgButton_clicked()));

    QString str;
    for (int i = 0, j = 1; i <= 90; i+= 5, j++)
    {
         str = QString("%1").arg(i);
         ui->tableWidget->setItem(j, 0, new QTableWidgetItem(QString("%1").arg(i)));
         ui->tableWidget->item(j,0)->setToolTip(str);
         ui->tableWidget->setItem(j, 1, new QTableWidgetItem(QString("%1").arg(i * pi / 180)));
         str = QString("%1").arg(i * pi / 180);
         ui->tableWidget->item(j,1)->setToolTip(str);
         ui->tableWidget->item(j,0)->setTextAlignment(Qt::AlignRight);
         ui->tableWidget->item(j,1)->setTextAlignment(Qt::AlignRight);

    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_sinButton_clicked()
{
    QString str;
    for (int i = 0, j = 1; i <= 90; i+= 5, j++)
    {
        ui->tableWidget->setItem(j, 2, new QTableWidgetItem(QString("%1").arg(sin(i * pi / 180))));
        ui->tableWidget->item(j,2)->setTextAlignment(Qt::AlignRight);
        str = QString("%1").arg(sin(i * pi / 180));
        ui->tableWidget->item(j,2)->setToolTip(str);
    }
}

void MainWindow::on_cosButton_clicked()
{
    QString str;
    for (int i = 0, j = 1; i <= 90; i+= 5, j++)
    {
        if (i == 90) {
            ui->tableWidget->setItem(j, 2, new QTableWidgetItem(QString("%1").arg(0)));
            str = "0";
        }
        else {
            ui->tableWidget->setItem(j, 2, new QTableWidgetItem(QString("%1").arg(cos(i * pi / 180))));
            str = QString("%1").arg(cos(i * pi / 180));
        }
        ui->tableWidget->item(j,2)->setToolTip(str);
        ui->tableWidget->item(j,2)->setTextAlignment(Qt::AlignRight);
    }
}

void MainWindow::on_tgButton_clicked()
{
    QString str;
    for (int i = 0, j = 1; i <= 90; i+= 5, j++)
    {
        if (i == 90)
        ui->tableWidget->setItem(j, 2, new QTableWidgetItem("Бесконечность"));
        else
        ui->tableWidget->setItem(j, 2, new QTableWidgetItem(QString("%1").arg(tan(i * pi / 180))));
        ui->tableWidget->item(j,2)->setTextAlignment(Qt::AlignRight);
        if (i != 90) {
            str = QString("%1").arg(tan(i * pi / 180));
            ui->tableWidget->item(j,2)->setToolTip(str);
        }
        if (i == 90) ui->tableWidget->item(j,2)->setToolTip("Бесконечность");
    }
}

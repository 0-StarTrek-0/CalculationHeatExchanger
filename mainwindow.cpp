#include <QVariant>
#include "tubeontube.h"
#include "casing.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pix(":/pref/Image/heat.png");
    int w = ui->ImageHeat->width();
    int h = ui->ImageHeat->height();
    ui->ImageHeat->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void on_Button_Exit()
{
    QApplication::quit();
}

void MainWindow::on_Button_Exit_clicked()
{
    QApplication::quit();
}

void MainWindow::on_Tubeontube_clicked()
{
    hide();
    window1 = new TubeonTube(this);
    window1->show();
}

void MainWindow::on_Casing_clicked()
{
    hide();
    window2 = new Casing(this);
    window2->show();
}

void MainWindow::on_Lamellar_clicked()
{
    hide();
    window3 = new Lamellar(this);
    window3->show();
}






#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tubeontube.h"
#include "casing.h"
#include "lamellar.h"



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Button_Exit_clicked();
    void on_Tubeontube_clicked();
    void on_Casing_clicked();
    void on_Lamellar_clicked();

private:
    Ui::MainWindow *ui;
    TubeonTube *window1;
    Casing *window2;
    Lamellar *window3;
};

#endif // MAINWINDOW_H

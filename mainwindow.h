#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sculptor.h"
#include "vector"

/**
* @file mainwindow.h
* @brief this header file will contain all required
* definitions and basic utilities functions for the program's Main window.
*
* @author Reyne Jasson
*
* @date 20/06/2019
*/

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

public slots:

void changePlane1(); //XY1
void changePlane2(); //ZX1
void changePlane3(); //YZ1
void changeShape1(); //PV
void changeShape2(); //CV
void changeShape3(); //PB
void changeShape4(); //CB
void changeShape5(); //PS
void changeShape6(); //CS
void changeShape7(); //PE
void changeShape8(); //PS
void rotClockWise();
void rotCClockWise();
void inverter();

void setSize();

void saveVECT();
void saveOFF();
void saveAll();


};

#endif // MAINWINDOW_H

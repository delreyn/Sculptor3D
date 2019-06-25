#include <QString>
#include <QProcess>
#include <QtDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sculptor.h"
#include "plotter.h"

/**
* @file mainwindow.cpp
* @brief this source file will contain all required
* definitions for control the mainwindow.
*
* @author Reyne Jasson
*
* @date 20/06/2019
*/

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Icons

    ui->pushButtonSV->setIcon(QIcon("E:/Escultor3D/icons/sav_ico.png"));
    ui->pushButtonCS->setIcon(QIcon("E:/Escultor3D/icons/icon1.png"));
    ui->pushButtonPS->setIcon(QIcon("E:/Escultor3D/icons/icon2.png"));
    ui->pushButtonPB->setIcon(QIcon("E:/Escultor3D/icons/icon_PutBx.png"));
    ui->pushButtonCB->setIcon(QIcon("E:/Escultor3D/icons/icon_CutBox.png"));

    ui->SizeX->setMinimum(1);
    ui->SizeY->setMinimum(1);
    ui->SizeZ->setMinimum(1);

    ui->SizeX->setMaximum(150);
    ui->SizeY->setMaximum(150);
    ui->SizeZ->setMaximum(150);

    ui->horizontalSliderSlice->setValue(15);

    ui->horizontalSliderRed->setMaximum(255);
    ui->horizontalSliderGreen->setMaximum(255);
    ui->horizontalSliderBlue->setMaximum(255);
    ui->horizontalSliderAlpha->setMaximum(255);
    ui->horizontalSliderSlice->setMaximum(ui->widgetPlotter->scpSizeZ -1);

    ui->horizontalSliderX->setMaximum(ui->widgetPlotter->scpSizeX-1);
    ui->horizontalSliderY->setMaximum(ui->widgetPlotter->scpSizeY-1);
    ui->horizontalSliderZ->setMaximum(ui->widgetPlotter->scpSizeZ-1);
    ui->horizontalSliderRD->setMaximum(ui->widgetPlotter->scpSizeX/2 -1);
    ui->horizontalSliderRX->setMaximum(ui->widgetPlotter->scpSizeX/2 -1);
    ui->horizontalSliderRY->setMaximum(ui->widgetPlotter->scpSizeY/2 -1);
    ui->horizontalSliderRZ->setMaximum(ui->widgetPlotter->scpSizeZ/2 -1);



    //////////////////////////////////

    connect(ui->GridSet,
            SIGNAL(clicked(bool)),
            this,
            SLOT(setSize()));

    connect(ui->pushButtonPV,
            SIGNAL(clicked(bool)),
            this,
            SLOT(changeShape1()));

    connect(ui->pushButtonCV,
            SIGNAL(clicked(bool)),
            this,
            SLOT(changeShape2()));

    connect(ui->pushButtonPB,
            SIGNAL(clicked(bool)),
            this,
            SLOT(changeShape3()));

    connect(ui->pushButtonCB,
            SIGNAL(clicked(bool)),
            this,
            SLOT(changeShape4()));

    connect(ui->pushButtonPS,
            SIGNAL(clicked(bool)),
            this,
            SLOT(changeShape5()));

    connect(ui->pushButtonCS,
            SIGNAL(clicked(bool)),
            this,
            SLOT(changeShape6()));

    connect(ui->pushButtonPE,
            SIGNAL(clicked(bool)),
            this,
            SLOT(changeShape7()));

    connect(ui->pushButtonCE,
            SIGNAL(clicked(bool)),
            this,
            SLOT(changeShape8()));

    connect(ui->pushButtonXY,
            SIGNAL(clicked(bool)),
            this,
            SLOT(changePlane1()));

    connect(ui->pushButtonXZ,
            SIGNAL(clicked(bool)),
            this,
            SLOT(changePlane2()));

    connect(ui->pushButtonYZ,
            SIGNAL(clicked(bool)),
            this,
            SLOT(changePlane3()));

    ///////////////////////////////////////////

    connect(ui->horizontalSliderX,
            SIGNAL(valueChanged(int)),
            ui->widgetPlotter,
            SLOT(changeSizeX(int)));

    connect(ui->horizontalSliderY,
            SIGNAL(valueChanged(int)),
            ui->widgetPlotter,
            SLOT(changeSizeY(int)));

    connect(ui->horizontalSliderZ,
            SIGNAL(valueChanged(int)),
            ui->widgetPlotter,
            SLOT(changeSizeZ(int)));

    connect(ui->horizontalSliderRD,
            SIGNAL(valueChanged(int)),
            ui->widgetPlotter,
            SLOT(changeRadius(int)));

    connect(ui->horizontalSliderRX,
            SIGNAL(valueChanged(int)),
            ui->widgetPlotter,
            SLOT(changeRadiusX(int)));

    connect(ui->horizontalSliderRY,
            SIGNAL(valueChanged(int)),
            ui->widgetPlotter,
            SLOT(changeRadiusY(int)));

    connect(ui->horizontalSliderRZ,
            SIGNAL(valueChanged(int)),
            ui->widgetPlotter,
            SLOT(changeRadiusZ(int)));

    connect(ui->horizontalSliderRed,
            SIGNAL(valueChanged(int)),
            ui->widgetPlotter,
            SLOT(changeRed(int)));

    connect(ui->horizontalSliderGreen,
            SIGNAL(valueChanged(int)),
            ui->widgetPlotter,
            SLOT(changeGreen(int)));

    connect(ui->horizontalSliderBlue,
            SIGNAL(valueChanged(int)),
            ui->widgetPlotter,
            SLOT(changeBlue(int)));

    connect(ui->horizontalSliderAlpha,
            SIGNAL(valueChanged(int)),
            ui->widgetPlotter,
            SLOT(changeAlpha(int)));

    connect(ui->horizontalSliderSlice,
            SIGNAL(valueChanged(int)),
            ui->widgetPlotter,
            SLOT(changeSlice(int)));

   /////////////////////////////////////////////

    connect(ui->pushButtonOFF,
            SIGNAL(clicked(bool)),
            this,
            SLOT(saveOFF()));

    connect(ui->pushButtonVECT,
            SIGNAL(clicked(bool)),
            this,
            SLOT(saveVECT()));

    connect(ui->pushButtonSV,
            SIGNAL(clicked(bool)),
            this,
            SLOT(saveAll()));

    ///////////////////////////////////

    connect(ui->horizontalSliderRed,
            SIGNAL(valueChanged(int)),
            ui->widgetColor,
            SLOT(changeRed2(int)));

    connect(ui->horizontalSliderGreen,
            SIGNAL(valueChanged(int)),
            ui->widgetColor,
            SLOT(changeGreen2(int)));

    connect(ui->horizontalSliderBlue,
            SIGNAL(valueChanged(int)),
            ui->widgetColor,
            SLOT(changeBlue2(int)));

    connect(ui->horizontalSliderAlpha,
            SIGNAL(valueChanged(int)),
            ui->widgetColor,
            SLOT(changeAlpha2(int)));
///////////////////////////////////////

    connect(ui->pushButtonRotClk,
            SIGNAL(clicked(bool)),
            this,
            SLOT(rotClockWise()));

    connect(ui->pushButtonRotCClk,
            SIGNAL(clicked(bool)),
            this,
            SLOT(rotCClockWise()));

    connect(ui->pushButtonInv,
            SIGNAL(clicked(bool)),
            this,
            SLOT(inverter()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

/**
* This method will be used to change the current plane to the XY plane
*
* @author Reyne Jasson
*
*
* @date 20/06/2019
*/
void MainWindow::changePlane1() //XY
{
    ui->widgetPlotter->plane = 1;
    emit ui->widgetPlotter->planeChosen(1);
    ui->widgetPlotter->slice = ui->widgetPlotter->scpSizeZ/2;
    ui->horizontalSliderSlice->setMaximum(ui->widgetPlotter->scpSizeZ -1);
    ui->widgetPlotter->repaint();

}
/**
* This method will be used to change the current plane to the XZ plane
*
* @author Reyne Jasson
*
*
* @date 20/06/2019
*/
void MainWindow::changePlane2() //XZ
{
    ui->widgetPlotter->plane = 2;
    emit ui->widgetPlotter->planeChosen(2);
    ui->horizontalSliderSlice->setMaximum(ui->widgetPlotter->scpSizeY -1);
    ui->widgetPlotter->slice = ui->widgetPlotter->scpSizeY/2;
    ui->widgetPlotter->repaint();
}
/**
* This method will be used to change the current plane to the YZ plane
*
* @author Reyne Jasson
*
*
* @date 20/06/2019
*/
void MainWindow::changePlane3() //YZ
{
    ui->widgetPlotter->plane = 3;
    emit ui->widgetPlotter->planeChosen(3);    
    ui->horizontalSliderSlice->setMaximum(ui->widgetPlotter->scpSizeX -1);
    ui->widgetPlotter->slice = ui->widgetPlotter->scpSizeX/2;
    ui->widgetPlotter->repaint();
}

/**
* This method will be used to change the objet to be drawn in the sculptor to a simple Voxel
*
* @author Reyne Jasson
*
*
* @date 20/06/2019
*/
void MainWindow::changeShape1() //PV
{
    ui->widgetPlotter->shape = 1;
}
/**
* This method will be used to change cut a voxel in the sculptor
*
* @author Reyne Jasson
*
*
* @date 20/06/2019
*/
void MainWindow::changeShape2() //CV
{
    ui->widgetPlotter->shape = 2;
}
/**
* This method will be used to put a box in the sculpture
*
* @author Reyne Jasson
*
*
* @date 20/06/2019
*/
void MainWindow::changeShape3() //PB
{
    ui->widgetPlotter->shape = 3;
}
/**
* Define a box to be removed from the sculptor
*
* @author Reyne Jasson
*
*
* @date 20/06/2019
*/
void MainWindow::changeShape4() //CB
{
    ui->widgetPlotter->shape = 4;
}
/**
* This method will be used to set a sphere to be drawn in the sculpture
*
* @author Reyne Jasson
*
*
* @date 20/06/2019
*/
void MainWindow::changeShape5() //PS
{
    ui->widgetPlotter->shape = 5;
}
/**
* This method will be used to cut a sphere in the sculptor
*
* @author Reyne Jasson
*
*
* @date 20/06/2019
*/
void MainWindow::changeShape6() //CS
{
    ui->widgetPlotter->shape = 6;
}
/**
* This method will be used to set an ellipsoid in the sculptor
*
* @author Reyne Jasson
*
*
* @date 20/06/2019
*/
void MainWindow::changeShape7() //PE
{
    ui->widgetPlotter->shape = 7;
}
/**
* This method will be used to set a sphere to be drawn in the sculptor
*
* @author Reyne Jasson
*
*
* @date 20/06/2019
*/
void MainWindow::changeShape8() //PS
{
    ui->widgetPlotter->shape = 8;
}

/**
* This method will be used to rotate the current plane to the 90º clockwise
*
* @author Reyne Jasson
*
*
* @date 20/06/2019
*/
void MainWindow::rotClockWise()
{
    switch(ui->widgetPlotter->plane){
    case 1: //XY1
        ui->widgetPlotter->plane = 4;
    break;
    case 2: //ZX1
        ui->widgetPlotter->plane = 5;
    break;
    case 3: //YZ1
        ui->widgetPlotter->plane = 6;
    break;
    case 4: //XY2
        ui->widgetPlotter->plane = 7;
    break;
    case 5: //ZX2
        ui->widgetPlotter->plane = 8;
    break;
    case 6: //YZ2
        ui->widgetPlotter->plane = 9;
    break;
    case 7:
        ui->widgetPlotter->plane = 10;
    break;
    case 8:
        ui->widgetPlotter->plane = 11;
    break;
    case 9:
        ui->widgetPlotter->plane = 12;
    break;
    case 10:
        ui->widgetPlotter->plane = 1;
    break;
    case 11:
        ui->widgetPlotter->plane = 2;
    break;
    case 12:
        ui->widgetPlotter->plane = 3;
    break;


    case 13:
        ui->widgetPlotter->plane = 16;
    break;
    case 14:
        ui->widgetPlotter->plane = 17;
    break;
    case 15:
        ui->widgetPlotter->plane = 18;
    break;
    case 16:
        ui->widgetPlotter->plane = 19;
    break;
    case 17:
        ui->widgetPlotter->plane = 20;
    break;
    case 18:
        ui->widgetPlotter->plane = 21;
    break;
    case 19:
        ui->widgetPlotter->plane = 22;
    break;
    case 20:
        ui->widgetPlotter->plane = 23;
    break;
    case 21:
        ui->widgetPlotter->plane = 24;
    break;
    case 22:
        ui->widgetPlotter->plane = 13;
    break;
    case 23:
        ui->widgetPlotter->plane = 14;
    break;
    case 24:
        ui->widgetPlotter->plane = 15;
    break;
    }
    ui->widgetPlotter->repaint();
}
/**
* This method will be used to rotate the current plane to the 90º counter-clockwise
*
* @author Reyne Jasson
*
*
* @date 20/06/2019
*/
void MainWindow::rotCClockWise()
{
    switch(ui->widgetPlotter->plane){
    case 1: //XY1
        ui->widgetPlotter->plane = 10;
    break;
    case 2: //ZX1
        ui->widgetPlotter->plane = 11;
    break;
    case 3: //YZ1
        ui->widgetPlotter->plane = 12;
    break;
    case 4: //XY2
        ui->widgetPlotter->plane = 1;
    break;
    case 5: //ZX2
        ui->widgetPlotter->plane = 2;
    break;
    case 6: //YZ2
        ui->widgetPlotter->plane = 3;
    break;
    case 7:
        ui->widgetPlotter->plane = 4;
    break;
    case 8:
        ui->widgetPlotter->plane = 5;
    break;
    case 9:
        ui->widgetPlotter->plane = 6;
    break;
    case 10:
        ui->widgetPlotter->plane = 7;
    break;
    case 11:
        ui->widgetPlotter->plane = 8;
    break;
    case 12:
        ui->widgetPlotter->plane = 9;
    break;


    case 13:
        ui->widgetPlotter->plane = 22;
    break;
    case 14:
        ui->widgetPlotter->plane = 23;
    break;
    case 15:
        ui->widgetPlotter->plane = 24;
    break;
    case 16:
        ui->widgetPlotter->plane = 13;
    break;
    case 17:
        ui->widgetPlotter->plane = 14;
    break;
    case 18:
        ui->widgetPlotter->plane = 15;
    break;
    case 19:
        ui->widgetPlotter->plane = 16;
    break;
    case 20:
        ui->widgetPlotter->plane = 17;
    break;
    case 21:
        ui->widgetPlotter->plane = 18;
    break;
    case 22:
        ui->widgetPlotter->plane = 19;
    break;
    case 23:
        ui->widgetPlotter->plane = 20;
    break;
    case 24:
        ui->widgetPlotter->plane = 21;
    break;
    }

    ui->widgetPlotter->repaint();
}


void MainWindow::inverter()
{
    switch(ui->widgetPlotter->plane){
    case 1: //XY1
        ui->widgetPlotter->plane = 13;
    break;
    case 2: //ZX1
        ui->widgetPlotter->plane = 14;
    break;
    case 3: //YZ1
        ui->widgetPlotter->plane = 15;
    break;
    case 4: //XY2
        ui->widgetPlotter->plane = 16;
    break;
    case 5: //ZX2
        ui->widgetPlotter->plane = 17;
    break;
    case 6: //YZ2
        ui->widgetPlotter->plane = 18;
    break;
    case 7:
        ui->widgetPlotter->plane = 19;
    break;
    case 8:
        ui->widgetPlotter->plane = 20;
    break;
    case 9:
        ui->widgetPlotter->plane = 21;
    break;
    case 10:
        ui->widgetPlotter->plane = 22;
    break;
    case 11:
        ui->widgetPlotter->plane = 23;
    break;
    case 12:
        ui->widgetPlotter->plane = 24;
    break;


    case 13:
        ui->widgetPlotter->plane = 1;
    break;
    case 14:
        ui->widgetPlotter->plane = 2;
    break;
    case 15:
        ui->widgetPlotter->plane = 3;
    break;
    case 16:
        ui->widgetPlotter->plane = 4;
    break;
    case 17:
        ui->widgetPlotter->plane = 5;
    break;
    case 18:
        ui->widgetPlotter->plane = 6;
    break;
    case 19:
        ui->widgetPlotter->plane = 7;
    break;
    case 20:
        ui->widgetPlotter->plane = 8;
    break;
    case 21:
        ui->widgetPlotter->plane = 9;
    break;
    case 22:
        ui->widgetPlotter->plane = 10;
    break;
    case 23:
        ui->widgetPlotter->plane = 11;
    break;
    case 24:
        ui->widgetPlotter->plane = 12;
    break;
    }

    ui->widgetPlotter->repaint();
}

/**
* This method will be set a new size to the sculptor grid
*
* @author Reyne Jasson
*
*
* @date 20/06/2019
*/
void MainWindow::setSize(){
    int sX = ui->SizeX->value();
    int sY = ui->SizeY->value();
    int sZ = ui->SizeZ->value();

   ui->widgetPlotter->changeSize(sX,sY,sZ);
  // ui->GridSet->setEnabled(false);
}

/**
* This method will be used to 'export a file in vect form 'view' a vect file in meshlab
*
* @author Reyne Jasson
*
*
* @date 20/06/2019
*/
void MainWindow::saveVECT()
{
    ui->widgetPlotter->cube->writeVECT("C:/Users/Reyne/Desktop/file.vect");


    QProcess *process = new QProcess(this);
    QString program = "C:/Program\ Files/VCG/MeshLab/MeshLab.exe";
    QString path = "C:/Users/Reyne/Desktop/file.vect";
    QStringList list;
    list << path;
    process->start(program, list);
    process->waitForFinished();
}
/**
* This method will be used to export a file in OFF form and 'view' in meshlab
*
* @author Reyne Jasson
*
*
* @date 20/06/2019
*/
void MainWindow::saveOFF()
{
    ui->widgetPlotter->cube->writeOFF("C:/Users/Reyne/Desktop/file.off");

    QProcess *process = new QProcess(this);
    QString program = "C:/Program\ Files/VCG/MeshLab/MeshLab.exe";
    QString path = "C:/Users/Reyne/Desktop/file.off";
    QStringList arg;
    arg << path;
    process->start(program,arg);
    process->waitForFinished();
}
/**
* This method will be used to export the sculptor file in both vect and OFF
*
* @author Reyne Jasson
*
*
* @date 20/06/2019
*/
void MainWindow::saveAll()
{
    ui->widgetPlotter->cube->writeVECT("C:/Users/Reyne/Desktop/file.vect");
    ui->widgetPlotter->cube->writeOFF("C:/Users/Reyne/Desktop/file.off");
}

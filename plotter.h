#ifndef PLOTTER_H
#define PLOTTER_H

#include <QWidget>
#include <QAction>
#include <QColor>
#include <QTimerEvent>
#include <vector>
#include "sculptor.h"

/**
* @file plotter.h
* @brief this header file will contain all required
* definitions and basic utilities functions for window abstract draw.
*
* @author Reyne Jasson
*
* @date 20/06/2019
*/

class Plotter : public QWidget
{
    Q_OBJECT
public:
    explicit Plotter(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void changeSize(int x,int y, int z);


    void drawShape(int shape, bool mousePressed);

    int plane;
    int shape;

    int scpSizeX, scpSizeY, scpSizeZ;
    Sculptor *cube;

    int colorRed;
    int colorGreen;
    int colorBlue;
    int transparency;

    int sizeX,sizeY,sizeZ;
    int radius, radiusX, radiusY,radiusZ;

    int radiusMax;
    int slice;


private:

    std::vector<std::vector<Voxel>> m;

    bool mousePressed;
    int mouseX,mouseY;

    int posX,posY,posZ;

    int sizeSquare;

signals:
  void moveX(int);
  void moveY(int);
  void clickX(int);
  void clickY(int);
  void mouseLinha(int);
  void mouseColuna(int);
  void mouseXY(int,int);
  void planeChosen(int);

public slots:

  void changeSizeX(int size);
  void changeSizeY(int size);
  void changeSizeZ(int size);
  void changeRadius(int rd);
  void changeRadiusX(int rx);
  void changeRadiusY(int ry);
  void changeRadiusZ(int rz);

  void changeRed(int red);
  void changeGreen(int green);
  void changeBlue(int blue);
  void changeAlpha(int alpha);

  void changeSlice(int pln);



};

#endif // PLOTTER_H

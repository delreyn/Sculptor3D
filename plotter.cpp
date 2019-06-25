#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QMouseEvent>
#include <QtDebug>
#include <vector>
#include <iostream>
#include "plotter.h"
#include "sculptor.h"

/**
* @file plotter.cpp
* @brief this source file will contain all required
* definitions for drawing the abstraction in the main window.
*
* @author Reyne Jasson
*
* @date 20/06/2019
*/

Plotter::Plotter(QWidget *parent) : QWidget(parent),
  colorRed(255), colorGreen(255), colorBlue(255), transparency(1.0),
  sizeX(0), sizeY(0), sizeZ(0),
  scpSizeX(50), scpSizeY(30), scpSizeZ(30),
  radius(0), radiusX(0), radiusY(0), radiusZ(0),
  shape(1), plane(1)
{

    cube = new Sculptor(scpSizeX,scpSizeY,scpSizeZ);

    slice=scpSizeZ/2;
    plane=1;
    cube->setColor(0.0,0.0,0.0,1.0);

}

void Plotter::paintEvent(QPaintEvent *event)
{
    QPainter pa(this);
    QPen pen;
    QBrush brush;
    pen.setColor(QColor(0,0,0));
    pen.setWidth(2);
      // entregando a caneta ao pintor
    pa.setPen(pen);
    brush.setColor(QColor(255,255,255));
    brush.setStyle(Qt::SolidPattern);
      // entregando o pincel ao pintor
    pa.setBrush(brush);
    m.clear();
    m = cube ->readMx(slice,plane);

    int dim1 = width()/m[0].size();
    int dim2 = height()/m.size();

    dim1 > dim2 ? sizeSquare=dim2 : sizeSquare=dim1;


    for(unsigned int i =0; i<m.size(); i++){
        for(unsigned int j =0; j<m[0].size(); j++){
            pa.drawRect(i*sizeSquare,j*sizeSquare,sizeSquare, sizeSquare);
        }
    }


 //   brush.setColor(QColor(colorRed,colorGreen,colorBlue,transparency));   //Cor setada por sliders
 //   brush.setStyle(Qt::SolidPattern);
 //   pa.setBrush(brush);


    for(unsigned int i=0; i<m.size();i++){    //trabalhar com iterators pra desenhar voxels ligados
       for(unsigned int j=0; j<m[0].size();j++){
            if(m[i][j].isOn){
                    brush.setColor(QColor(m[i][j].r,m[i][j].g,m[i][j].b,m[i][j].a));   //Cor setada por sliders
                    brush.setStyle(Qt::SolidPattern);
                    pa.setBrush(brush);
                    int xcenter =i*sizeSquare;
                    int ycenter =j*sizeSquare;
                    pa.drawEllipse(xcenter,ycenter,sizeSquare,sizeSquare);
            }
       }
    }

}

void Plotter::mouseMoveEvent(QMouseEvent *event){
    emit moveX(event->x());
    emit moveY(event->y());

    mouseX = (event->x())/sizeSquare;
    mouseY = (event->y())/sizeSquare;

    switch(plane){
    case 1:
        posX=mouseX;
        posY=mouseY;
        posZ=slice;
    break;
    case 2:
        posX=mouseY;
        posY=slice;
        posZ=mouseX;
    break;
    case 3:
        posX=slice;
        posY=mouseX;
        posZ=mouseY;
    break;
    case 4:
        posX=mouseY;
        posY=scpSizeY-1-mouseX;
        posZ=slice;
    break;
    case 5:
        posX=scpSizeX-1-mouseX;
        posY=slice;
        posZ=mouseY;
    break;
    case 6:
        posX=slice;
        posY=mouseY;
        posZ=scpSizeZ-1-mouseX;
    break;
    case 7:
        posX=scpSizeX-1-mouseX;
        posY=scpSizeY-1-mouseY;
        posZ=slice;
    break;
    case 8:
        posX=scpSizeX-1-mouseY;
        posY=slice;
        posZ=scpSizeZ-1-mouseX;
    break;
    case 9:
        posX=slice;
        posY=scpSizeY-1-mouseX;
        posZ=scpSizeZ-1-mouseY;
    break;
    case 10:
        posX=scpSizeX-1-mouseY;
        posY=mouseX;
        posZ=slice;
    break;
    case 11:
        posX=mouseX;
        posY=slice;
        posZ=scpSizeZ-1-mouseY;
    break;
    case 12:
        posX=slice;
        posY=scpSizeY-1-mouseY;
        posZ=mouseX;
    break;
    case 13:
        posX=mouseY;
        posY=mouseX;
        posZ=slice;
    break;
    case 14:
        posX=mouseY;
        posY=slice;
        posZ=mouseX;
    break;
    case 15:
        posX=slice;
        posY=mouseX;
        posZ=mouseY;
    break;
    case 16:
        posX=mouseY;
        posY=mouseX;
        posZ=slice;
    break;
    case 17:
        posX=mouseX;
        posY=slice;
        posZ=mouseY;
    break;
    case 18:
        posX=slice;
        posY=mouseY;
        posZ=mouseX;
    break;
    case 19:
        posX=mouseX;
        posY=mouseY;
        posZ=slice;
    break;
    case 20:
        posX=mouseY;
        posY=slice;
        posZ=mouseX;
    break;
    case 21:
        posX=slice;
        posY=mouseX;
        posZ=mouseY;
    break;
    case 22:
        posX=mouseY;
        posY=mouseX;
        posZ=slice;
    break;
    case 23:
        posX=mouseX;
        posY=slice;
        posZ=mouseY;
    break;
    case 24:
        posX=slice;
        posY=mouseY;
        posZ=mouseX;
    break;
    }
    emit mouseLinha(posX);
    emit mouseColuna(posY);

    Plotter::drawShape(shape,mousePressed);


}

void Plotter::mousePressEvent(QMouseEvent *event){
  if(event->button() == Qt::LeftButton){
    emit clickX(event->x());
    emit clickY(event->y());
    mousePressed = true;
    mouseX = (event->x())/sizeSquare;
    mouseY = (event->y())/sizeSquare;

    switch(plane){
    case 1:
        posX=mouseX;
        posY=mouseY;
        posZ=slice;
    break;
    case 2:
        posX=mouseY;
        posY=slice;
        posZ=mouseX;
    break;
    case 3:
        posX=slice;
        posY=mouseX;
        posZ=mouseY;
    break;
    case 4:
        posX=mouseY;
        posY=scpSizeY-1-mouseX;
        posZ=slice;
    break;
    case 5:
        posX=scpSizeX-1-mouseX;
        posY=slice;
        posZ=mouseY;
    break;
    case 6:
        posX=slice;
        posY=mouseY;
        posZ=scpSizeZ-1-mouseX;
    break;
    case 7:
        posX=scpSizeX-1-mouseX;
        posY=scpSizeY-1-mouseY;
        posZ=slice;
    break;
    case 8:
        posX=scpSizeX-1-mouseY;
        posY=slice;
        posZ=scpSizeZ-1-mouseX;
    break;
    case 9:
        posX=slice;
        posY=scpSizeY-1-mouseX;
        posZ=scpSizeZ-1-mouseY;
    break;
    case 10:
        posX=scpSizeX-1-mouseY;
        posY=mouseX;
        posZ=slice;
    break;
    case 11:
        posX=mouseX;
        posY=slice;
        posZ=scpSizeZ-1-mouseY;
    break;
    case 12:
        posX=slice;
        posY=scpSizeY-1-mouseY;
        posZ=mouseX;
    break;
    case 13:
        posX=mouseY;
        posY=mouseX;
        posZ=slice;
    break;
    case 14:
        posX=mouseY;
        posY=slice;
        posZ=mouseX;
    break;
    case 15:
        posX=slice;
        posY=mouseX;
        posZ=mouseY;
    break;
    case 16:
        posX=mouseY;
        posY=mouseX;
        posZ=slice;
    break;
    case 17:
        posX=mouseX;
        posY=slice;
        posZ=mouseY;
    break;
    case 18:
        posX=slice;
        posY=mouseY;
        posZ=mouseX;
    break;
    case 19:
        posX=mouseX;
        posY=mouseY;
        posZ=slice;
    break;
    case 20:
        posX=mouseY;
        posY=slice;
        posZ=mouseX;
    break;
    case 21:
        posX=slice;
        posY=mouseX;
        posZ=mouseY;
    break;
    case 22:
        posX=mouseY;
        posY=mouseX;
        posZ=slice;
    break;
    case 23:
        posX=mouseX;
        posY=slice;
        posZ=mouseY;
    break;
    case 24:
        posX=slice;
        posY=mouseY;
        posZ=mouseX;
    break;
    }
    emit mouseLinha(posX);
    emit mouseColuna(posY);

    Plotter::drawShape(shape,mousePressed);
  }
}


void Plotter::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
       mousePressed = false;
    }
}


void Plotter::drawShape(int shape, bool mousePressed){

  if(mousePressed){
    if(shape == 1) //PutVoxel
    {
       cube->setColor(colorRed,colorGreen,colorBlue,transparency);   //setada por sliders
       cube->putVoxel(posX,posY,posZ);        //setada onde clickado
    }
    if(shape == 2) //CutVoxel
    {
       cube->cutVoxel(posX,posY,posZ);
    }
    if(shape == 3) //PutBox
    {
        cube->setColor(colorRed,colorGreen,colorBlue,transparency);
        cube->putBox(posX,(posX+sizeX),posY,(posY+sizeY),posZ,(posZ+sizeZ));

    }
    if(shape == 4) //CutBox
    {
       cube->cutBox(posX,(posX+sizeX),posY,(posY+sizeY),posZ,(posZ+sizeZ));
    }
    if(shape == 5) //PutSphere
    {
        cube->setColor(colorRed,colorGreen,colorBlue,transparency);
        cube->putSphere(posX,posY,posZ,radius);

    }
    if(shape == 6) //CutSphere
    {
       cube->cutSphere(posX,posY,posZ,radius);;
    }
    if(shape == 7) //PutEllipsoid
    {
        cube->setColor(colorRed,colorGreen,colorBlue,transparency);
        cube->putEllipsoid(posX,posY,posZ,radiusX,radiusY,radiusZ);

    }
    if(shape == 8) //Cut
    {
       cube->cutEllipsoid(posX,posY,posZ,radiusX,radiusY,radiusZ);
    }
    repaint();
    }
}

void Plotter::changeRed(int red)
{
    colorRed = red;
}
void Plotter::changeGreen(int green)
{
    colorGreen = green;
}
void Plotter::changeBlue(int blue)
{
    colorBlue = blue;
}
void Plotter::changeAlpha(int alpha)
{
    transparency = alpha;
}


void Plotter::changeSizeX(int size)
{
    sizeX=size;
}
void Plotter::changeSizeY(int size)
{
    sizeY=size;
}
void Plotter::changeSizeZ(int size)
{
    sizeZ=size;
}
void Plotter::changeRadius(int rd)
{
    radius=rd;
}
void Plotter::changeRadiusX(int rx)
{
    radiusX=rx;
}
void Plotter::changeRadiusY(int ry)
{
    radiusY=ry;
}
void Plotter::changeRadiusZ(int rz)
{
    radiusZ=rz;
}
void Plotter::changeSlice(int pln)
{
    slice = pln;
    repaint();
}
void Plotter::changeSize(int x,int y, int z){
    delete cube;
    cube = nullptr;
    cube = new Sculptor(x,y,z);
    scpSizeX = x;
    scpSizeY = y;
    scpSizeZ = z;
    repaint();
}


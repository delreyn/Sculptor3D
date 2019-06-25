#ifndef COLORWINDOW_H
#define COLORWINDOW_H

#include <QWidget>
#include <QColor>

/**
* @file colorwindow.h
* @brief this header file will contain all required
* definitions and basic utilities functions for set colors to the scuptor.
*
* @author Reyne Jasson
*
* @date 20/06/2019
*/

class ColorWindow : public QWidget
{
    Q_OBJECT
public:
    explicit ColorWindow(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
    int colorRed,colorGreen,colorBlue,alpha;

private:

public slots:
    void changeRed2(int red);
    void changeGreen2(int green);
    void changeBlue2(int blue);
    void changeAlpha2(int alpha);
};

#endif // COLORWINDOW_H

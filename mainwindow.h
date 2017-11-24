#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <surface.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void paintEvent(QPaintEvent *);

private:
    Ui::MainWindow *ui;
    Surface surface;
    // начало координат
    static const int displayXO = 750;
    static const int displayYO = 350;
    // смещение display x,y для оси OX
    static const double xBiasOX = -0.8660;
    static const double yBiasOX = 0.5;
    // смещение display x,y для оси OY
    static const double xBiasOY = 0.8660;
    static const double yBiasOY = 0.5;
    // смещение display x,y для оси OZ
    static const double xBiasOZ = 0;
    static const double yBiasOZ = -1;

    static const int lenghtOX = 300;
    static const int lenghtOY = 300;
    static const int lenghtOZ = 300;

    static const double buildXOYdotXBias = 0.8660;
    static const double buildXOYdotYBias = 0.5;
    int buildXOYDotsBiasMatrix[3][3] = {{1,0,0},
                                    {0,1,0},
                                    {0,0,1}};
    double buildXOYDotsResultMatrix[2][3];
    double displayDot[2];
    void createDisplayCoordinateOfDot(double, double, double);

    double cub[8][3];
    double displayDotsOfCub[8][2];

    double borders[4][3];
    double displayDotsOfBorders[4][2];

    bool cubIsCreate = false;
    bool bordersIsCreate = false;
    bool surfaceisCreate = false;

    int uCount;
    int wCount;
    double*** displayDotsofSurface;

public slots:
    void displayCub();
    void displaySurface();
    void displayboundaries();
};

#endif // MAINWINDOW_H

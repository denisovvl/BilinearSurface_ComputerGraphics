#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qpainter.h"
#include <QDebug>
#include <math.h>
#define PI 3.14159265

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    uCount = surface.uCount;
    wCount = surface.wCount;
    ui->setupUi(this);
    setWindowTitle("Lab3");
    showMaximized();
    setMouseTracking(true);
    connect(ui->buildCub, SIGNAL(clicked(bool)),this,SLOT(displayCub()));
    connect(ui->displayBoundaries, SIGNAL(clicked(bool)),this,SLOT(displayboundaries()));
    connect(ui->buildSurface, SIGNAL(clicked(bool)),this,SLOT(displaySurface()));
    connect(ui->turnSurface, SIGNAL(clicked(bool)),this,SLOT(turnSurface()));
}

MainWindow::~MainWindow()
{
    for(int i = 0; i < uCount; i++){
        for(int j = 0; j < wCount; j++){
            delete [] displayDotsofSurface[i][j];
        }
        delete [] displayDotsofSurface[i];
    }
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *){
    QPainter p(this);
    p.setPen(QPen(Qt::black,1,Qt::SolidLine));
    // рисуем OX
    p.drawLine(displayXO,displayYO,displayXO + xBiasOX*lenghtOX,displayYO + yBiasOX*lenghtOX);
    p.drawText(displayXO + xBiasOX*(lenghtOX + 10),displayYO + yBiasOX*(lenghtOX + 10),"X");
    // рисуем OY
    p.drawLine(displayXO,displayYO,displayXO + xBiasOY*lenghtOY,displayYO + yBiasOY*lenghtOY);
        p.drawText(displayXO + xBiasOY*(lenghtOY + 10),displayYO + yBiasOY*(lenghtOY + 10),"Y");
    // рисуем OZ
    p.drawLine(displayXO,displayYO,displayXO + xBiasOZ*lenghtOZ,displayYO + yBiasOZ*lenghtOZ);
    p.drawText(displayXO + xBiasOZ*(lenghtOZ + 10),displayYO + yBiasOZ*(lenghtOZ + 10),"Z");

    // задаем точки куба
    if(cubIsCreate){
        p.setPen(QPen(Qt::black,3,Qt::SolidLine));
        for(int i = 0; i < 8; i++){
            p.drawPoint(displayDotsOfCub[i][0], displayDotsOfCub[i][1]);
            //qDebug() << "P" << i+1 << ": " << displayDotsOfCub[i][0] << displayDotsOfCub[i][1];
        }
        // соединяем точки куба
        p.setPen(QPen(Qt::black,1,Qt::DashLine));
        p.drawLine(displayDotsOfCub[1][0],displayDotsOfCub[1][1], displayDotsOfCub[2][0],displayDotsOfCub[2][1]);
        p.drawLine(displayDotsOfCub[2][0],displayDotsOfCub[2][1], displayDotsOfCub[3][0],displayDotsOfCub[3][1]);
        p.drawLine(displayDotsOfCub[3][0],displayDotsOfCub[3][1], displayDotsOfCub[7][0],displayDotsOfCub[7][1]);
        p.drawLine(displayDotsOfCub[2][0],displayDotsOfCub[2][1], displayDotsOfCub[6][0],displayDotsOfCub[6][1]);
        p.drawLine(displayDotsOfCub[1][0],displayDotsOfCub[1][1], displayDotsOfCub[5][0],displayDotsOfCub[5][1]);
        p.drawLine(displayDotsOfCub[4][0],displayDotsOfCub[4][1], displayDotsOfCub[5][0],displayDotsOfCub[5][1]);
        p.drawLine(displayDotsOfCub[5][0],displayDotsOfCub[5][1], displayDotsOfCub[6][0],displayDotsOfCub[6][1]);
        p.drawLine(displayDotsOfCub[6][0],displayDotsOfCub[6][1], displayDotsOfCub[7][0],displayDotsOfCub[7][1]);
        p.drawLine(displayDotsOfCub[7][0],displayDotsOfCub[7][1], displayDotsOfCub[4][0],displayDotsOfCub[4][1]);
        p.setPen(QPen(Qt::black,1,Qt::DashLine));
        p.drawLine(displayDotsOfCub[0][0],displayDotsOfCub[0][1], displayDotsOfCub[1][0],displayDotsOfCub[1][1]);
        p.drawLine(displayDotsOfCub[0][0],displayDotsOfCub[0][1], displayDotsOfCub[3][0],displayDotsOfCub[3][1]);
        p.drawLine(displayDotsOfCub[0][0],displayDotsOfCub[0][1], displayDotsOfCub[4][0],displayDotsOfCub[4][1]);
    }
    // задаем точки границ поверхности
    if(bordersIsCreate){
        p.setPen(QPen(Qt::red,5,Qt::SolidLine));
        for(int i = 0; i < 4; i++){
            p.drawPoint(displayDotsOfBorders[i][0], displayDotsOfBorders[i][1]);
            //qDebug() << "Bord P" << ": " << displayDotsOfBorders[i][0] << displayDotsOfBorders[i][1];
        }
        p.setPen(QPen(Qt::red,2,Qt::SolidLine));
        p.drawLine(displayDotsOfBorders[0][0], displayDotsOfBorders[0][1], displayDotsOfBorders[1][0], displayDotsOfBorders[1][1]);
        p.drawLine(displayDotsOfBorders[1][0], displayDotsOfBorders[1][1], displayDotsOfBorders[2][0], displayDotsOfBorders[2][1]);
        p.drawLine(displayDotsOfBorders[2][0], displayDotsOfBorders[2][1], displayDotsOfBorders[3][0], displayDotsOfBorders[3][1]);
        p.drawLine(displayDotsOfBorders[3][0], displayDotsOfBorders[3][1], displayDotsOfBorders[0][0], displayDotsOfBorders[0][1]);
    }
    // рисуем поверхность
    if(surfaceisCreate){
        p.setPen(QPen(Qt::red,1,Qt::SolidLine));
        for(int i = 1; i < uCount; i++){
            for(int j = 1; j < wCount; j++){
                p.drawLine(displayDotsofSurface[i][j][0], displayDotsofSurface[i][j][1], displayDotsofSurface[i][j-1][0], displayDotsofSurface[i][j-1][1]);
                p.drawLine(displayDotsofSurface[i][j][0], displayDotsofSurface[i][j][1], displayDotsofSurface[i-1][j][0], displayDotsofSurface[i-1][j][1]);
                //p.drawPoint(displayDotsofSurface[i][j][0], displayDotsofSurface[i][j][1]);
            }
        }
    }
}

void MainWindow::createDisplayCoordinateOfDot(double x, double y, double z){
    x *= 30;
    y *= 30;
    z *= 30;
    double oxVector[2][3];
    oxVector[0][0] = displayXO;
    oxVector[0][1] = displayYO;
    oxVector[0][2] = 1;
    oxVector[1][0] = displayXO + xBiasOX*x;
    oxVector[1][1] = displayYO + yBiasOX*x;
    oxVector[1][2] = 1;
    buildXOYDotsBiasMatrix[2][0] = buildXOYdotXBias*y;
    buildXOYDotsBiasMatrix[2][1] = buildXOYdotYBias*y;
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 3; j++){
            buildXOYDotsResultMatrix[i][j] = oxVector[i][0]*buildXOYDotsBiasMatrix[0][j] +
                                             oxVector[i][1]*buildXOYDotsBiasMatrix[1][j] +
                                             oxVector[i][2]*buildXOYDotsBiasMatrix[2][j];
        }
    }
    displayDot[0] = buildXOYDotsResultMatrix[1][0];
    displayDot[1] = buildXOYDotsResultMatrix[1][1] - z;
}

void MainWindow::displayCub(){
    bool p1XBool, p1YBool, p1ZBool,
         p2XBool, p2YBool, p2ZBool,
         p3XBool, p3YBool, p3ZBool,
         p4XBool, p4YBool, p4ZBool,
         p5XBool, p5YBool, p5ZBool,
         p6XBool, p6YBool, p6ZBool,
         p7XBool, p7YBool, p7ZBool,
         p8XBool, p8YBool, p8ZBool;
    cub[0][0] = ui->P1xCub->text().toDouble(&p1XBool);
    cub[1][0] = ui->P2xCub->text().toDouble(&p2XBool);
    cub[2][0] = ui->P3xCub->text().toDouble(&p3XBool);
    cub[3][0] = ui->P4xCub->text().toDouble(&p4XBool);
    cub[4][0] = ui->P5xCub->text().toDouble(&p5XBool);
    cub[5][0] = ui->P6xCub->text().toDouble(&p6XBool);
    cub[6][0] = ui->P7xCub->text().toDouble(&p7XBool);
    cub[7][0] = ui->P8xCub->text().toDouble(&p8XBool);

    cub[0][1] = ui->P1yCub->text().toDouble(&p1YBool);
    cub[1][1] = ui->P2yCub->text().toDouble(&p2YBool);
    cub[2][1] = ui->P3yCub->text().toDouble(&p3YBool);
    cub[3][1] = ui->P4yCub->text().toDouble(&p4YBool);
    cub[4][1] = ui->P5yCub->text().toDouble(&p5YBool);
    cub[5][1] = ui->P6yCub->text().toDouble(&p6YBool);
    cub[6][1] = ui->P7yCub->text().toDouble(&p7YBool);
    cub[7][1] = ui->P8yCub->text().toDouble(&p8YBool);

    cub[0][2] = ui->P1zCub->text().toDouble(&p1ZBool);
    cub[1][2] = ui->P2zCub->text().toDouble(&p2ZBool);
    cub[2][2] = ui->P3zCub->text().toDouble(&p3ZBool);
    cub[3][2] = ui->P4zCub->text().toDouble(&p4ZBool);
    cub[4][2] = ui->P5zCub->text().toDouble(&p5ZBool);
    cub[5][2] = ui->P6zCub->text().toDouble(&p6ZBool);
    cub[6][2] = ui->P7zCub->text().toDouble(&p7ZBool);
    cub[7][2] = ui->P8zCub->text().toDouble(&p8ZBool);

    if(p1XBool && p1YBool && p1ZBool && p2XBool && p2YBool && p2ZBool && p3XBool && p3YBool && p3ZBool &&
       p4XBool && p4YBool && p4ZBool && p5XBool && p5YBool && p5ZBool && p6XBool && p6YBool && p6ZBool &&
       p7XBool && p7YBool && p7ZBool && p8XBool && p8YBool && p8ZBool){
       for(int i = 0; i < 8; i++){
           createDisplayCoordinateOfDot(cub[i][0], cub[i][1], cub[i][2]);
           displayDotsOfCub[i][0] = displayDot[0];
           displayDotsOfCub[i][1] = displayDot[1];
       }
       cubIsCreate = true;
    }else{
        cubIsCreate = false;
    }
    this->update();
}
void MainWindow::displayboundaries(){
    bool p00XBool, p00YBool, p00ZBool,
         p01XBool, p01YBool, p01ZBool,
         p11XBool, p11YBool, p11ZBool,
         p10XBool, p10YBool, p10ZBool;
    borders[0][0] = ui->P00xCub->text().toDouble(&p00XBool);
    borders[0][1] = ui->P00yCub->text().toDouble(&p00ZBool);
    borders[0][2] = ui->P00zCub->text().toDouble(&p00YBool);

    borders[1][0] = ui->P01xCub->text().toDouble(&p01XBool);
    borders[1][1] = ui->P01yCub->text().toDouble(&p01YBool);
    borders[1][2] = ui->P01zCub->text().toDouble(&p01ZBool);

    borders[2][0] = ui->P11xCub->text().toDouble(&p11XBool);
    borders[2][1] = ui->P11yCub->text().toDouble(&p11YBool);
    borders[2][2] = ui->P11zCub->text().toDouble(&p11ZBool);

    borders[3][0] = ui->P10xCub->text().toDouble(&p10XBool);
    borders[3][1] = ui->P10yCub->text().toDouble(&p10YBool);
    borders[3][2] = ui->P10zCub->text().toDouble(&p10ZBool);

    if(p00XBool && p00YBool && p00ZBool &&
       p01XBool && p01YBool && p01ZBool &&
       p11XBool && p11YBool && p11ZBool &&
       p10XBool && p10YBool && p10ZBool){
        for(int i = 0; i < 4; i++){
            createDisplayCoordinateOfDot(borders[i][0], borders[i][1], borders[i][2]);
            displayDotsOfBorders[i][0] = displayDot[0];
            displayDotsOfBorders[i][1] = displayDot[1];
        }
        surface.setp00(borders[0]);
        surface.setp01(borders[1]);
        surface.setp11(borders[2]);
        surface.setp10(borders[3]);
        bordersIsCreate = true;
    }else{
        bordersIsCreate = false;
    }
    this->update();
}
void MainWindow::displaySurface(){
    if(bordersIsCreate){
        surf;
        surface.createSurface();
        surf = surface.getSurface();
    //qDebug() << "displaySurface - я тут работаю";
        displayDotsofSurface = new double**[uCount];
        for(int i = 0; i < uCount; i++){
            displayDotsofSurface[i] = new double*[wCount];
            for(int j = 0; j < wCount; j++){
                displayDotsofSurface[i][j] = new double[2];
            }
        }
    //qDebug() << "displaySurface - я тут работаю2";
        for(int i = 0; i < uCount; i++){
            for(int j = 0; j < wCount;j++){
                createDisplayCoordinateOfDot(surf[i][j][0],surf[i][j][1],surf[i][j][2]);
                displayDotsofSurface[i][j][0] = displayDot[0];
                displayDotsofSurface[i][j][1] = displayDot[1];
            }
        }
    //qDebug() << "displaySurface - я тут работаю3";
        surfaceisCreate = true;
        this->update();
    }else{
        surfaceisCreate = false;
    }
}
void MainWindow::turnSurface(){
    bool angleTurnXBool, angleTurnYBool, angleTurnZBool;
    double angleTurnX, angleTurnY, angleTurnZ;
    angleTurnX = ui->angleTurnX->text().toDouble(&angleTurnXBool);
    angleTurnY = ui->angleTurnY->text().toDouble(&angleTurnYBool);
    angleTurnZ = ui->angleTurnZ->text().toDouble(&angleTurnZBool);
    if(angleTurnXBool){
        surface.createTurnMatrixX(angleTurnX);
        surface.turnSurfaceAboutX();
        createTurnMatrixX(angleTurnX);
        turnCubAboutX();
        turnBordersAboutX();
    }
    if(angleTurnYBool){
        surface.createTurnMatrixY(angleTurnY);
        surface.turnSurfaceAboutY();
        createTurnMatrixY(angleTurnY);
        turnCubAboutY();
        turnBordersAboutY();
    }
    if(angleTurnZBool){
        surface.createTurnMatrixZ(angleTurnZ);
        surface.turnSurfaceAboutZ();
        createTurnMatrixZ(angleTurnZ);
        turnCubAboutZ();
        turnBordersAboutZ();
    }
    if(angleTurnXBool || angleTurnYBool || angleTurnZBool){
        if(bordersIsCreate){
            surf;
            surf = surface.getSurface();
        //qDebug() << "turnSurface - я тут работаю2";
            for(int i = 0; i < uCount; i++){
                for(int j = 0; j < wCount;j++){
                    createDisplayCoordinateOfDot(surf[i][j][0],surf[i][j][1],surf[i][j][2]);
                    displayDotsofSurface[i][j][0] = displayDot[0];
                    displayDotsofSurface[i][j][1] = displayDot[1];
                }
            }
        //qDebug() << "turnSurface - я тут работаю3";
            surfaceisCreate = true;
            this->update();
        }else{
            surfaceisCreate = false;
        }
    }
}

void MainWindow::createTurnMatrixX(double alphaX){
    turnMatrixX[0][0] = 1;
    turnMatrixX[0][1] = 0;
    turnMatrixX[0][2] = 0;
    turnMatrixX[1][0] = 0;
    turnMatrixX[1][1] = cos(alphaX*PI/180);
    turnMatrixX[1][2] = -sin(alphaX*PI/180);
    turnMatrixX[2][0] = 0;
    turnMatrixX[2][1] = sin(alphaX*PI/180);
    turnMatrixX[2][2] = cos(alphaX*PI/180);
}
void MainWindow::createTurnMatrixY(double alphaY){
    turnMatrixY[0][0] = cos(alphaY*PI/180);
    turnMatrixY[0][1] = 0;
    turnMatrixY[0][2] = sin(alphaY*PI/180);
    turnMatrixY[1][0] = 0;
    turnMatrixY[1][1] = 1;
    turnMatrixY[1][2] = 0;
    turnMatrixY[2][0] = -sin(alphaY*PI/180);
    turnMatrixY[2][1] = 0;
    turnMatrixY[2][2] = cos(alphaY*PI/180);
}
void MainWindow::createTurnMatrixZ(double alphaZ){
    turnMatrixZ[0][0] = cos(alphaZ*PI/180);
    turnMatrixZ[0][1] = -sin(alphaZ*PI/180);
    turnMatrixZ[0][2] = 0;
    turnMatrixZ[1][0] = sin(alphaZ*PI/180);
    turnMatrixZ[1][1] = cos(alphaZ*PI/180);
    turnMatrixZ[1][2] = 0;
    turnMatrixZ[2][0] = 0;
    turnMatrixZ[2][1] = 0;
    turnMatrixZ[2][2] = 1;
}

void MainWindow::turnCubAboutX(){
    double coord[3];
    for(int i = 0; i < 8; i++){
            // поворачиваем куб
            coord[0] = cub[i][0];
            coord[1] = cub[i][1];
            coord[2] = cub[i][2];
            cub[i][0] = coord[0]*turnMatrixX[0][0] +
                        coord[1]*turnMatrixX[0][1] +
                        coord[2]*turnMatrixX[0][2];
            cub[i][1] = coord[0]*turnMatrixX[1][0] +
                        coord[1]*turnMatrixX[1][1] +
                        coord[2]*turnMatrixX[1][2];
            cub[i][2] = coord[0]*turnMatrixX[2][0] +
                        coord[1]*turnMatrixX[2][1] +
                        coord[2]*turnMatrixX[2][2];
            // переводим в координаты дисплея
            createDisplayCoordinateOfDot(cub[i][0], cub[i][1], cub[i][2]);
            displayDotsOfCub[i][0] = displayDot[0];
            displayDotsOfCub[i][1] = displayDot[1];
    }

}
void MainWindow::turnCubAboutY(){
    double coord[3];
    for(int i = 0; i < 8; i++){
            // поворачиваем куб
            coord[0] = cub[i][0];
            coord[1] = cub[i][1];
            coord[2] = cub[i][2];
            cub[i][0] = coord[0]*turnMatrixY[0][0] +
                        coord[1]*turnMatrixY[0][1] +
                        coord[2]*turnMatrixY[0][2];
            cub[i][1] = coord[0]*turnMatrixY[1][0] +
                        coord[1]*turnMatrixY[1][1] +
                        coord[2]*turnMatrixY[1][2];
            cub[i][2] = coord[0]*turnMatrixY[2][0] +
                        coord[1]*turnMatrixY[2][1] +
                        coord[2]*turnMatrixY[2][2];
            // переводим в координаты дисплея
            createDisplayCoordinateOfDot(cub[i][0], cub[i][1], cub[i][2]);
            displayDotsOfCub[i][0] = displayDot[0];
            displayDotsOfCub[i][1] = displayDot[1];
    }
}
void MainWindow::turnCubAboutZ(){
    double coord[3];
    for(int i = 0; i < 8; i++){
            // поворачиваем куб
            coord[0] = cub[i][0];
            coord[1] = cub[i][1];
            coord[2] = cub[i][2];
            cub[i][0] = coord[0]*turnMatrixZ[0][0] +
                        coord[1]*turnMatrixZ[0][1] +
                        coord[2]*turnMatrixZ[0][2];
            cub[i][1] = coord[0]*turnMatrixZ[1][0] +
                        coord[1]*turnMatrixZ[1][1] +
                        coord[2]*turnMatrixZ[1][2];
            cub[i][2] = coord[0]*turnMatrixZ[2][0] +
                        coord[1]*turnMatrixZ[2][1] +
                        coord[2]*turnMatrixZ[2][2];
            // переводим в координаты дисплея
            createDisplayCoordinateOfDot(cub[i][0], cub[i][1], cub[i][2]);
            displayDotsOfCub[i][0] = displayDot[0];
            displayDotsOfCub[i][1] = displayDot[1];
    }
}
void MainWindow::turnBordersAboutX(){
    double coord[3];
    for(int i = 0; i < 4; i++){
            // поворачиваем границы
            coord[0] = borders[i][0];
            coord[1] = borders[i][1];
            coord[2] = borders[i][2];
            borders[i][0] = coord[0]*turnMatrixX[0][0] +
                            coord[1]*turnMatrixX[0][1] +
                            coord[2]*turnMatrixX[0][2];
            borders[i][1] = coord[0]*turnMatrixX[1][0] +
                            coord[1]*turnMatrixX[1][1] +
                            coord[2]*turnMatrixX[1][2];
            borders[i][2] = coord[0]*turnMatrixX[2][0] +
                            coord[1]*turnMatrixX[2][1] +
                            coord[2]*turnMatrixX[2][2];
            // переводим в координаты дисплея
            createDisplayCoordinateOfDot(borders[i][0], borders[i][1], borders[i][2]);
            displayDotsOfBorders[i][0] = displayDot[0];
            displayDotsOfBorders[i][1] = displayDot[1];
    }
}
void MainWindow::turnBordersAboutY(){
    double coord[3];
    for(int i = 0; i < 4; i++){
            // поворачиваем границы
            coord[0] = borders[i][0];
            coord[1] = borders[i][1];
            coord[2] = borders[i][2];
            borders[i][0] = coord[0]*turnMatrixY[0][0] +
                            coord[1]*turnMatrixY[0][1] +
                            coord[2]*turnMatrixY[0][2];
            borders[i][1] = coord[0]*turnMatrixY[1][0] +
                            coord[1]*turnMatrixY[1][1] +
                            coord[2]*turnMatrixY[1][2];
            borders[i][2] = coord[0]*turnMatrixY[2][0] +
                            coord[1]*turnMatrixY[2][1] +
                            coord[2]*turnMatrixY[2][2];
            // переводим в координаты дисплея
            createDisplayCoordinateOfDot(borders[i][0], borders[i][1], borders[i][2]);
            displayDotsOfBorders[i][0] = displayDot[0];
            displayDotsOfBorders[i][1] = displayDot[1];
    }
}
void MainWindow::turnBordersAboutZ(){
    double coord[3];
    for(int i = 0; i < 4; i++){
            // поворачиваем границы
            coord[0] = borders[i][0];
            coord[1] = borders[i][1];
            coord[2] = borders[i][2];
            borders[i][0] = coord[0]*turnMatrixZ[0][0] +
                            coord[1]*turnMatrixZ[0][1] +
                            coord[2]*turnMatrixZ[0][2];
            borders[i][1] = coord[0]*turnMatrixZ[1][0] +
                            coord[1]*turnMatrixZ[1][1] +
                            coord[2]*turnMatrixZ[1][2];
            borders[i][2] = coord[0]*turnMatrixZ[2][0] +
                            coord[1]*turnMatrixZ[2][1] +
                            coord[2]*turnMatrixZ[2][2];
            // переводим в координаты дисплея
            createDisplayCoordinateOfDot(borders[i][0], borders[i][1], borders[i][2]);
            displayDotsOfBorders[i][0] = displayDot[0];
            displayDotsOfBorders[i][1] = displayDot[1];
    }
}

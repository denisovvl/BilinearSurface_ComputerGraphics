#include "surface.h"
#include <qDebug>
#include <math.h>
#define PI 3.14159265
Surface::Surface()
{

}
void Surface::setp00(double* _p00){
    p00[0] = _p00[0];
    p00[1] = _p00[1];
    p00[2] = _p00[2];

}
void Surface::setp01(double* _p01){
    p01[0] = _p01[0];
    p01[1] = _p01[1];
    p01[2] = _p01[2];
}
void Surface::setp11(double* _p11){
    p11[0] = _p11[0];
    p11[1] = _p11[1];
    p11[2] = _p11[2];
}
void Surface::setp10(double* _p10){
    p10[0] = _p10[0];
    p10[1] = _p10[1];
    p10[2] = _p10[2];
}

double* Surface::getp00(){
    return p00;
}
double* Surface::getp01(){
    return p01;
}
double* Surface::getp11(){
    return p11;
}
double* Surface::getp10(){
    return p10;
}
void Surface::createSurface(){
    surface = new double**[uCount];
    for(int i = 0; i < uCount;i++){
        surface[i] = new double*[wCount];
        for(int j = 0; j < wCount; j++)
            surface[i][j] = new double[3];
    }
   
    int uIndex = 0;
    int wIndex = 0;
    double a, b, c, d;
    for(int u = MIN_U; u < MAX_U; u+=3){
        if(u > 100){
            a = 0;
            b = 1;
        }else{
            a = 1 - ((double)(u))/100;
            b = ((double)(u))/100;
        }
        for(int w = MIN_W; w < MAX_W; w +=3){
            if(w > 100){
                c = 0;
                d = 1;
            }else{
                c = 1 - ((double)(w))/100;
                d = ((double)(w))/100;
            }
            surface[uIndex][wIndex][0] = a*(p00[0]*c + p01[0]*d) + b*(p10[0]*c + p11[0]*d);
            surface[uIndex][wIndex][1] = a*(p00[1]*c + p01[1]*d) + b*(p10[1]*c + p11[1]*d);
            surface[uIndex][wIndex][2] = a*(p00[2]*c + p01[2]*d) + b*(p10[2]*c + p11[2]*d);
            wIndex++;
        }
        uIndex++;
        wIndex = 0;
    }
}

double*** Surface::getSurface(){
    return surface;
}
void Surface::createTurnMatrixX(double alphaX){
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
void Surface::createTurnMatrixY(double alphaY){
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
void Surface::createTurnMatrixZ(double alphaZ){
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
void Surface::turnSurfaceAboutX(){
    double coord[3];
    for(int i = 0; i < uCount; i++){
        for(int j = 0; j < wCount; j++){
            coord[0] = surface[i][j][0];
            coord[1] = surface[i][j][1];
            coord[2] = surface[i][j][2];
            surface[i][j][0] = coord[0]*turnMatrixX[0][0] +
                               coord[1]*turnMatrixX[0][1] +
                               coord[2]*turnMatrixX[0][2];
            surface[i][j][1] = coord[0]*turnMatrixX[1][0] +
                               coord[1]*turnMatrixX[1][1] +
                               coord[2]*turnMatrixX[1][2];
            surface[i][j][2] = coord[0]*turnMatrixX[2][0] +
                               coord[1]*turnMatrixX[2][1] +
                               coord[2]*turnMatrixX[2][2];
        }
    }
}
void Surface::turnSurfaceAboutY(){
    double coord[3];
    for(int i = 0; i < uCount; i++){
        for(int j = 0; j < wCount; j++){
            coord[0] = surface[i][j][0];
            coord[1] = surface[i][j][1];
            coord[2] = surface[i][j][2];
            surface[i][j][0] = coord[0]*turnMatrixY[0][0] +
                               coord[1]*turnMatrixY[0][1] +
                               coord[2]*turnMatrixY[0][2];
            surface[i][j][1] = coord[0]*turnMatrixY[1][0] +
                               coord[1]*turnMatrixY[1][1] +
                               coord[2]*turnMatrixY[1][2];
            surface[i][j][2] = coord[0]*turnMatrixY[2][0] +
                               coord[1]*turnMatrixY[2][1] +
                               coord[2]*turnMatrixY[2][2];
        }
    }
}
void Surface::turnSurfaceAboutZ(){
    double coord[3];
    for(int i = 0; i < uCount; i++){
        for(int j = 0; j < wCount; j++){
            coord[0] = surface[i][j][0];
            coord[1] = surface[i][j][1];
            coord[2] = surface[i][j][2];
            surface[i][j][0] = coord[0]*turnMatrixZ[0][0] +
                               coord[1]*turnMatrixZ[0][1] +
                               coord[2]*turnMatrixZ[0][2];
            surface[i][j][1] = coord[0]*turnMatrixZ[1][0] +
                               coord[1]*turnMatrixZ[1][1] +
                               coord[2]*turnMatrixZ[1][2];
            surface[i][j][2] = coord[0]*turnMatrixZ[2][0] +
                               coord[1]*turnMatrixZ[2][1] +
                               coord[2]*turnMatrixZ[2][2];
        }
    }
}
void Surface::reset(){
    for(int i = 0; i < uCount; i++){
        for(int j = 0; j < wCount; j++){
            delete [] surface[i][j];
        }
        delete [] surface[i];
    }
}

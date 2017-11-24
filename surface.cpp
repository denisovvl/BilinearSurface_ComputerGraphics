#include "surface.h"
#include <qDebug>
Surface::Surface()
{

}
void Surface::setp00(double* _p00){
    p00[0] = _p00[0];
    p00[1] = _p00[1];
    p00[2] = _p00[2];
    qDebug() << "p00: " << p00[0] << " " << p00[1] << " " << p00[2];

}
void Surface::setp01(double* _p01){
    p01[0] = _p01[0];
    p01[1] = _p01[1];
    p01[2] = _p01[2];
    qDebug() << "p01: " << p01[0] << " " << p01[1] << " " << p01[2];
}
void Surface::setp11(double* _p11){
    p11[0] = _p11[0];
    p11[1] = _p11[1];
    p11[2] = _p11[2];
    qDebug() << "p11: " << p11[0] << " " << p11[1] << " " << p11[2];
}
void Surface::setp10(double* _p10){
    p10[0] = _p10[0];
    p10[1] = _p10[1];
    p10[2] = _p10[2];
    qDebug() << "p10: " << p10[0] << " " << p10[1] << " " << p10[2];

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
    qDebug() << "createSurface - я тут работаю1";
    surface = new double**[uCount];
    for(int i = 0; i < uCount;i++){
        surface[i] = new double*[wCount];
        for(int j = 0; j < wCount; j++)
            surface[i][j] = new double[3];
    }
    int uIndex = 0;
    int wIndex = 0;
    double a, b, c, d;
    for(int u = MIN_U; u < MAX_U-1; u+=3){
        a = 1 - ((double)(u))/100;
        b = ((double)(u))/100;
        for(int w = MIN_W; w < MAX_W-1; w +=3){
            c = 1 - ((double)(w))/100;
            d = ((double)(w))/100;
            //qDebug() << "createSurface - я тут работаю1.1 {" << "u:" << u << ";w" << w << "}" << "uIndex:" << uIndex << ";wIndex" << wIndex << "}";
            surface[uIndex][wIndex][0] = a*(p00[0]*c + p01[0]*d) + b*(p10[0]*c + p11[0]*d);
            surface[uIndex][wIndex][1] = a*(p00[1]*c + p01[1]*d) + b*(p10[1]*c + p11[1]*d);
            surface[uIndex][wIndex][2] = a*(p00[2]*c + p01[2]*d) + b*(p10[2]*c + p11[2]*d);
            wIndex++;
            //qDebug() << "createSurface - я тут работаю1.2";
        }

        uIndex++;
        wIndex = 0;
    }
    qDebug() << "createSurface - я тут работаю2";
}

double*** Surface::getSurface(){
    return surface;
}

void Surface::reset(){
    for(int i = 0; i < uCount; i++){
        for(int j = 0; j < wCount; j++){
            delete [] surface[i][j];
        }
        delete [] surface[i];
    }
}

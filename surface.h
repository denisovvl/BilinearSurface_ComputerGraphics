#ifndef SURFACE_H
#define SURFACE_H


class Surface
{
private:
    double p00[3], p01[3],p11[3],p10[3];
    static const int MIN_U = 0;
    static const int MAX_U = 100;
    static const int MIN_W = 0;
    static const int MAX_W = 100;
    double turnMatrixX[3][3]; // матрица поворота для оси X
    double turnMatrixY[3][3]; // матрица поворота для оси Y
    double turnMatrixZ[3][3]; // матрица поворота для оси Z


public:
    Surface();
    static const int uCount = MAX_U/3 + 1; // Добавляем еще по одному элеvенту для u/w = 1
    static const int wCount = MAX_W/3 + 1;
    //static const int countOfDotsOnSurface = uCount*wCount;
    double*** surface;
    void setp00(double*);
    void setp01(double*);
    void setp11(double*);
    void setp10(double*);
    double* getp00();
    double* getp01();
    double* getp11();
    double* getp10();
    void createSurface();
    double*** getSurface();
    void createTurnMatrixX(double);
    void createTurnMatrixY(double);
    void createTurnMatrixZ(double);
    void turnSurfaceAboutX();
    void turnSurfaceAboutY();
    void turnSurfaceAboutZ();
    void reset();
};

#endif // SURFACE_H

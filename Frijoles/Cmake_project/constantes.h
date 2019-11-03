#ifndef CONSTANTES_H
#define CONSTANTES_H

#include <math.h>

const double g=9.8, K=1.0e4, Gamma=50, Kcundall=10, MU=0.4;
const double Lx=10,Ly=60;
const int Nx=7,Ny=7, N=Nx*Ny;

const double Zi=0.1786178958448091e0;
const double Lambda=0.2123418310626054*(-1);
const double Xi=0.06626458266981849*(-1);

const double Coeficiente1=(1-2*Lambda)/2;
const double Coeficiente2=(1-2*(Xi+Zi));

const double UD2Pi = 1/(2*M_PI);

#endif

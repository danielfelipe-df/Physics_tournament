#ifndef CILINDRO_H
#define CILINDRO_H

#include <iostream>
#include <fstream>
#include <cmath>
#include "constantes.h"
#include "Vector.h"

class Cilindro
{
private:
  vector3D r,V,F,omega,tau; double m,R,L,theta,I;
public:
  void Inicie(double x0,double y0,double z0,double Vx0,double Vy0,double Vz0,double theta0,double omega0,double m0,double R0,double L0);
  void BorreFuerzaYTorque(void){F.cargue(0,0,0);tau.cargue(0,0,0);};
  void AgregueFuerza(vector3D dF){F+=dF;};
  void AgregueTorque(vector3D dtau){tau+=dtau;};
  void Mueva_r(double dt,double Coeficiente);
  void Mueva_V(double dt,double Coeficiente);
  void Dibujese(void);
  double Getx(void){return r.x();}; //Inline
  double Gety(void){return r.y();}; //Inline
  double Getz(void){return r.z();}; //Inline
  double GetVx(void){return V.x();}; //Inline
  friend class Colisionador;
  friend class Cuerpo;
};

#endif // CILINDRO_H

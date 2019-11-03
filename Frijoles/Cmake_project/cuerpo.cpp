#include "cuerpo.h"

void Cuerpo::Inicie(double x0,double y0,double z0,double Vx0,double Vy0,double Vz0,double theta0,double omega0,double m0,double R0)
{
  r.cargue(x0,y0,z0); V.cargue(Vx0,Vy0,Vz0); omega.cargue(0,0,omega0);
  theta=theta0; m=m0; R=R0; I=2.0/5*m*R*R;
}

void Cuerpo::Mueva_r(double dt,double Coeficiente)
{
  r+=V*(dt*Coeficiente); theta+=omega.z()*(dt*Coeficiente);
}

void Cuerpo::Mueva_V(double dt,double Coeficiente)
{
  V+=F*(dt*Coeficiente/m);  omega+=tau*(dt*Coeficiente/I);
}

void Cuerpo::Dibujese(void)
{
  std::cout << " , " << r.x() << "+" << R << "*cos(t)," << r.y() << "+" << R << "*sin(t) , ";
  std::cout << r.x() << "+" << R*cos(theta)/7.0 << "*t," << r.y() << "+" << R*sin(theta)/7.0 << "*t";
}

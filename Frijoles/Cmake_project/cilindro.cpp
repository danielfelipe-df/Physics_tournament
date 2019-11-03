#include "cilindro.h"

void Cilindro::Inicie(double x0, double y0, double z0, double Vx0, double Vy0, double Vz0, double theta0, double omega0, double m0, double R0, double L0)
{
  r.cargue(x0,y0,z0); V.cargue(Vx0,Vy0,Vz0); omega.cargue(0,0,omega0);
  theta=theta0; m=m0; R=R0; L=L0;  I=m*R*R/12.0;
}

void Cilindro::Mueva_r(double dt, double Coeficiente)
{
  r+=V*(dt*Coeficiente); theta+=omega.z()*(dt*Coeficiente);
}

void Cilindro::Mueva_V(double dt,double Coeficiente)
{
  V+=F*(dt*Coeficiente/m);  omega+=tau*(dt*Coeficiente/I);
}

void Cilindro::Dibujese(void)
{
  std::cout << " , " << r.x() + R << "+" << L*cos(theta)*UD2Pi << "*t," << r.y() + R << "+" << L*sin(theta)*UD2Pi << "*t , ";
  std::cout << r.x() - R << "+" << L*cos(theta)*UD2Pi << "*t," << r.y() - R << "+" << L*sin(theta)*UD2Pi << "*t , ";
  std::cout << r.x() << "+" << L*cos(theta)*UD2Pi << "*t + " <<  R*UD2Pi << "*cos(t*0.5)," << r.y() << "+" << L*sin(theta)*UD2Pi << "*t + " << R*UD2Pi << "*sin(-t*0.5) , ";
  std::cout << r.x() << "-" << L*cos(theta)*UD2Pi << "*t + " <<  R*UD2Pi << "*cos(t*0.5)," << r.y() << "-" << L*sin(theta)*UD2Pi << "*t + " << R*UD2Pi << "*sin(-t*0.5)";
  //std::cout << r.x() << "+" << R*UD2Pi << "*cos(t*0.5)," << r.y() << "+" << R*UD2Pi << "*sin(-t*0.5) , ";
  //std::cout << r.x() << "+" << R*cos(theta)*UD2Pi << "*t," << r.y() << "+" << R*sin(theta)*UD2Pi << "*t";
}

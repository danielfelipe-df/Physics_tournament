#include <iostream>
#include <fstream>
#include <cmath>
#include "constantes.h"
#include "Vector.h"
#include "Random64.h"
#include "cuerpo.h"
#include "colisionador.h"

//Esta función me inicia la animación
void InicieAnimacion(void);

//Esta función me inicia el cuadr de la animación
void InicieCuadro(void);

//Esta función termina el cuadro de la animación
void TermineCuadro(void);


int main(void)
{
  Cuerpo Molecula[N+4];
  Colisionador Newton;
  Crandom ran64(1);
  double t,tdibujo,dt=1.0e-3;
  double m0=1,R0=0.5;
  int i,j,n;
  double kT=10;


  InicieAnimacion();

  //--------------INICIALIZACION----------------------------

  //PAREDES
  double Mpared=100*m0, Rpared=10000;
  //---------------(x0  ,       y0,z0,Vx0,Vy0,Vz0,theta0,omega0, m0,R0);
  //Pared arriba
  Molecula[N  ].Inicie(Lx/2,Ly+Rpared, 0, 0, 0, 0,     0,     0, Mpared, Rpared);
  //Pared abajo
  Molecula[N+1].Inicie(Lx/2,  -Rpared, 0, 0, 0, 0,     0,     0, Mpared, Rpared);
  //Pared derecha
  Molecula[N+2].Inicie(Lx+Rpared,Ly/2, 0, 0, 0, 0,     0,     0, Mpared, Rpared);
  //Pared izquierda
  Molecula[N+3].Inicie(  -Rpared,Ly/2, 0, 0, 0, 0,     0,     0, Mpared, Rpared);

  //MOLECULAS
  double dx=Lx/(Nx+1), dy=Ly/(Ny+1), x0,y0;
  double V0=sqrt(2*kT/m0), theta,Vx0,Vy0;
  for(i=0;i<Nx;i++)
    for(j=0;j<Ny;j++){
      x0=(i+1)*dx; y0=(j+1)*dy;
      theta=2*M_PI*ran64.r(); Vx0=V0*cos(theta); Vy0=V0*sin(theta);
      //---------------------(x0,y0,z0,Vx0,Vy0,Vz0,theta0,omega0,m0, R0)
      Molecula[i*Ny+j].Inicie(x0,y0, 0,Vx0,Vy0,  0,     0,     0,m0, R0);
    }

  //Agregar Fuerza de Impulso
  vector3D impulso_vector;  impulso_vector.cargue(0,100.0*g,0);

  //------------CORRER LA SIMULACION-------------------------
  double T=20,Teq=20;
  double tend=15.0, tlim=10.0, trange=1.0, tlimdown=tlim-trange, tlimup=tlim+trange;

  for(t=tdibujo=0; t<tlimdown; t+=dt,tdibujo+=dt){
    if(tdibujo>T/800){
      //if(t>Teq) for(int n=0;n<N;n++) std::cout<<Molecula[n].GetVx()<<std::endl;
      InicieCuadro();
      for(i=0;i<N;i++) Molecula[i].Dibujese();
      TermineCuadro();

      tdibujo=0;
    }

    //Moverlo según PEFRL Orden 4
    for(i=0;i<N;i++) Molecula[i].Mueva_r(dt,Zi);
    Newton.CalculeTodasLasFuerzas(Molecula,dt);
    for(i=0;i<N;i++) Molecula[i].Mueva_V(dt,Coeficiente1);
    for(i=0;i<N;i++) Molecula[i].Mueva_r(dt,Xi);
    Newton.CalculeTodasLasFuerzas(Molecula,dt);
    for(i=0;i<N;i++) Molecula[i].Mueva_V(dt,Lambda);
    for(i=0;i<N;i++) Molecula[i].Mueva_r(dt,Coeficiente2);
    Newton.CalculeTodasLasFuerzas(Molecula,dt);
    for(i=0;i<N;i++) Molecula[i].Mueva_V(dt,Lambda);
    for(i=0;i<N;i++) Molecula[i].Mueva_r(dt,Xi);
    Newton.CalculeTodasLasFuerzas(Molecula,dt);
    for(i=0;i<N;i++) Molecula[i].Mueva_V(dt,Coeficiente1);
    for(i=0;i<N;i++) Molecula[i].Mueva_r(dt,Zi);
  }

  //Este es el for en el que se aplica la fuerza
  for(t=tlimdown; t<tlimup; t+=dt,tdibujo+=dt){
    if(tdibujo>T/800){
      //if(t>Teq) for(int n=0;n<N;n++) std::cout<<Molecula[n].GetVx()<<std::endl;
      InicieCuadro();
      for(i=0;i<N;i++) Molecula[i].Dibujese();
      TermineCuadro();

      tdibujo=0;
    }

    //Moverlo según PEFRL Orden 4
    for(i=0;i<N;i++) Molecula[i].Mueva_r(dt,Zi);
    Newton.CalculeTodasLasFuerzas(Molecula,dt);
    for(i=0;i<N;i++) if(Molecula[i].r.y() < 2.0*R0) Molecula[i].AgregueFuerza(impulso_vector);
    for(i=0;i<N;i++) Molecula[i].Mueva_V(dt,Coeficiente1);
    for(i=0;i<N;i++) Molecula[i].Mueva_r(dt,Xi);
    Newton.CalculeTodasLasFuerzas(Molecula,dt);
    for(i=0;i<N;i++) if(Molecula[i].r.y() < 2.0*R0) Molecula[i].AgregueFuerza(impulso_vector);
    for(i=0;i<N;i++) Molecula[i].Mueva_V(dt,Lambda);
    for(i=0;i<N;i++) Molecula[i].Mueva_r(dt,Coeficiente2);
    Newton.CalculeTodasLasFuerzas(Molecula,dt);
    for(i=0;i<N;i++) if(Molecula[i].r.y() < 2.0*R0) Molecula[i].AgregueFuerza(impulso_vector);
    for(i=0;i<N;i++) Molecula[i].Mueva_V(dt,Lambda);
    for(i=0;i<N;i++) Molecula[i].Mueva_r(dt,Xi);
    Newton.CalculeTodasLasFuerzas(Molecula,dt);
    for(i=0;i<N;i++) if(Molecula[i].r.y() < 2.0*R0) Molecula[i].AgregueFuerza(impulso_vector);
    for(i=0;i<N;i++) Molecula[i].Mueva_V(dt,Coeficiente1);
    for(i=0;i<N;i++) Molecula[i].Mueva_r(dt,Zi);
  }

  for(t=tlimup; t<tend; t+=dt,tdibujo+=dt){
    if(tdibujo>T/800){
      //if(t>Teq) for(int n=0;n<N;n++) std::cout<<Molecula[n].GetVx()<<std::endl;
      InicieCuadro();
      for(i=0;i<N;i++) Molecula[i].Dibujese();
      TermineCuadro();

      tdibujo=0;
    }

    //Moverlo según PEFRL Orden 4
    for(i=0;i<N;i++) Molecula[i].Mueva_r(dt,Zi);
    Newton.CalculeTodasLasFuerzas(Molecula,dt);
    for(i=0;i<N;i++) Molecula[i].Mueva_V(dt,Coeficiente1);
    for(i=0;i<N;i++) Molecula[i].Mueva_r(dt,Xi);
    Newton.CalculeTodasLasFuerzas(Molecula,dt);
    for(i=0;i<N;i++) Molecula[i].Mueva_V(dt,Lambda);
    for(i=0;i<N;i++) Molecula[i].Mueva_r(dt,Coeficiente2);
    Newton.CalculeTodasLasFuerzas(Molecula,dt);
    for(i=0;i<N;i++) Molecula[i].Mueva_V(dt,Lambda);
    for(i=0;i<N;i++) Molecula[i].Mueva_r(dt,Xi);
    Newton.CalculeTodasLasFuerzas(Molecula,dt);
    for(i=0;i<N;i++) Molecula[i].Mueva_V(dt,Coeficiente1);
    for(i=0;i<N;i++) Molecula[i].Mueva_r(dt,Zi);
  }


  //------------IMPRIMIR RESULTADOS-------------------------
  return 0;
}


//------------------ Funciones Globales -----------------
void InicieAnimacion(void)
{
  //std::cout<<"set terminal gif animate"<<std::endl;
  //std::cout<<"set output 'pelicula.gif'"<<std::endl;
  std::cout<<"unset key"<<std::endl;
  std::cout<<"set xrange[-10:"<<Lx+10<<"]"<<std::endl;
  std::cout<<"set yrange[-10:"<<Ly+10<<"]"<<std::endl;
  std::cout<<"set size ratio -1"<<std::endl;
  std::cout<<"set parametric"<<std::endl;
  std::cout<<"set trange [0:7]"<<std::endl;
  std::cout<<"set isosamples 12"<<std::endl;
}

void InicieCuadro(void)
{
  std::cout<<"plot 0,0 ";
  std::cout<<" , "<<Lx/7<<"*t,0";        //pared de abajo
  std::cout<<" , "<<Lx/7<<"*t,"<<Ly;     //pared de arriba
  std::cout<<" , 0,"<<Ly/7<<"*t";        //pared de la izquierda
  std::cout<<" , "<<Lx<<","<<Ly/7<<"*t"; //pared de la derecha
}

void TermineCuadro(void)
{
  std::cout<<std::endl;
}



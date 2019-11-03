#include <iostream>
#include <fstream>
#include <cmath>
#include "constantes.h"
#include "Vector.h"
#include "Random64.h"
#include "cuerpo.h"
#include "cilindro.h"
#include "colisionador.h"

//Esta función me inicia la animación
void InicieAnimacion(void);

//Esta función me inicia el cuadr de la animación
void InicieCuadro(void);

//Esta función termina el cuadro de la animación
void TermineCuadro(void);


int main(void)
{
  Cuerpo Pelota;
  Cilindro Frijol;
  Colisionador Newton;
  Crandom ran64(1);
  double t,tdibujo,dt=1.0e-3;
  double m0=1,R0=0.5;
  int i,j;
  double kT=10;

  Frijol.Inicie(10,10,0,0,0,0,M_PI,0,10,5,20);

  InicieAnimacion();

  InicieCuadro();
  Frijol.Dibujese();
  TermineCuadro();
  std::cout << "pause 10" << std::endl;

  //--------------INICIALIZACION----------------------------

  //MOLECULAS


  //------------CORRER LA SIMULACION-------------------------
  /*
  double T=20,Teq=20, Tmax=15.0;

  for(t=tdibujo=0; t<Tmax; t+=dt,tdibujo+=dt){
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
  */

  //------------IMPRIMIR RESULTADOS-------------------------
  return 0;
}


//------------------ Funciones Globales -----------------
void InicieAnimacion(void)
{
  //std::cout<<"set terminal gif animate"<<std::endl;
  //std::cout<<"set output 'pelicula.gif'"<<std::endl;
  std::cout<<"unset key"<<std::endl;
  //std::cout<<"set xrange[-10:"<<Lx+10<<"]"<<std::endl;
  //std::cout<<"set yrange[-10:"<<Ly+10<<"]"<<std::endl;
  std::cout<<"set size ratio -1"<<std::endl;
  std::cout<<"set parametric"<<std::endl;
  std::cout<<"set trange [-pi:pi]"<<std::endl;
  std::cout<<"set isosamples 12"<<std::endl;
}

void InicieCuadro(void)
{
  std::cout<<"plot 0,0 ";/*
  std::cout<<" , "<<Lx/7<<"*t,0";        //pared de abajo
  std::cout<<" , "<<Lx/7<<"*t,"<<Ly;     //pared de arriba
  std::cout<<" , 0,"<<Ly/7<<"*t";        //pared de la izquierda
  std::cout<<" , "<<Lx<<","<<Ly/7<<"*t"; //pared de la derecha*/
}

void TermineCuadro(void)
{
  std::cout<<std::endl;
}



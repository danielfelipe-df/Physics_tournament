#ifndef COLISIONADOR_H
#define COLISIONADOR_H

#include <iostream>
#include <fstream>
#include <cmath>
#include "constantes.h"
#include "cuerpo.h"

//------------------ Clase Colisionador -----------------
class Colisionador{
private:
  vector3D ele[N+3][N+3]; bool EstabaEnContacto[N+3][N+3];
public:
  void Inicie(void);
  void CalculeFuerzaEntre(Cuerpo & Molecula1, Cuerpo & Molecula2, vector3D & ele, bool & EstabaEnContacto, double dt);
  void CalculeTodasLasFuerzas(Cuerpo * Molecula,double dt);
};

#endif // COLISIONADOR_H

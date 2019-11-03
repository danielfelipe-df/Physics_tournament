#include "colisionador.h"

void Colisionador::Inicie(void){
  for(int i=0;i<N+3;i++)
    for(int j=0;j<N+3;j++)
      {ele[i][j].cargue(0,0,0); EstabaEnContacto[i][j]=false;}
}

void Colisionador::CalculeFuerzaEntre(Cuerpo & Molecula1,Cuerpo & Molecula2,vector3D & ele, bool & EstabaEnContacto, double dt)
{
  double ERRF=1e-8;
  vector3D dr=Molecula2.r-Molecula1.r; double Norma_dr=norma(dr);
  double s=(Molecula2.R+Molecula1.R)-Norma_dr;
  if(s>0){ //Si hay choque
    //Calcular cantidades auxilares
    vector3D n=dr/Norma_dr;
    vector3D Vc=Molecula2.V-Molecula1.V -((Molecula1.omega*Molecula1.R+Molecula2.omega*Molecula2.R)^n);
    double Componente_Vcn=(Vc*n); vector3D Vcn=n*Componente_Vcn, Vct=Vc-Vcn;
    double Norma_Vct=norma(Vct);
    vector3D t; if(Norma_Vct<ERRF) t.cargue(0,0,0); else t=Vct/Norma_Vct;

    //CALCULAR FUERZAS NORMALES
    double ComponenteFn;
    //Fuerza de Hertz
    ComponenteFn=K*pow(s,1.5);
    //Fuerza de choque inelastico
    double m12=(Molecula1.m*Molecula2.m)/(Molecula1.m+Molecula2.m);
    ComponenteFn-=m12*sqrt(s)*Gamma*Componente_Vcn; if(ComponenteFn<0) ComponenteFn=0;
    //Fuerza normal total
    vector3D Fn=n*ComponenteFn;

    //CALCULAR FUERZAS TANGENCIALES
    //Fuerza de friccion estatica
    ele+=Vct*dt; vector3D Ft=ele*(-Kcundall);
    //fuerza de friccion cinetica
    double FtMax=MU*fabs(ComponenteFn);
    if(norma(Ft)>FtMax) Ft=ele*(-FtMax/norma(ele));

    //ENSAMBLAR LA FUERZA TOTAL Y CARGARLA
    vector3D F2=Fn+Ft;
    Molecula2.AgregueFuerza(F2);
    Molecula1.AgregueFuerza(F2*(-1));
    vector3D nCruzF2=n^F2;
    Molecula2.AgregueTorque(nCruzF2*(-Molecula2.R));
    Molecula1.AgregueTorque(nCruzF2*(-Molecula1.R));

    EstabaEnContacto=true;
  }
  else if(EstabaEnContacto){
    ele.cargue(0,0,0); EstabaEnContacto=false;
  }
}
void Colisionador::CalculeTodasLasFuerzas(Cuerpo * Molecula,double dt){
  int i,j;
  //Borrar fuerzas y torques
  for(i=0;i<(N+3);i++) Molecula[i].BorreFuerzaYTorque();
  //Agregar Fuerza de Gravedad;
  vector3D g_vector; g_vector.cargue(0,-g,0);
  for(i=0;i<N;i++) Molecula[i].AgregueFuerza(g_vector*Molecula[i].m);
  //Agregue las fuerzas de los choques
  for(i=0;i<N;i++)
    for(j=i+1;j<(N+3);j++)
      CalculeFuerzaEntre(Molecula[i],Molecula[j],ele[i][j],EstabaEnContacto[i][j],dt);
}

#include <stdio.h>
#include <stdlib.h>

/*Declaracion e funciones*/
void func(double *f, double *x, int tamano);
/*Main*/
int main
{
  int i;
  double x_min = 0.0;
  double x_max = 1.0;
  double y_min = 0.0;
  int puntos = 10000;
  double dx = (x_max-x_min)/puntos;
  double *x;
  x = malloc(puntos*sizeof(int));
  double *y;
  y = malloc(puntos*sizeof(int));
  x[0] = x_min;
  /*Inicializamos x*/
  for(i=1;i<puntos;i++){
    x[i] = x[i-1] + dx;
  }
  /*Inicializamos y = exp(-x)*/
  func(y,x,puntos);
}
/*Funcion que calcula exp(-x)*/
void func(double *f, double *x, int tamano)
{
  int i;
  for(i=0;i<tamano;i++) {
    f[i] = exp(-x[i]);
    }
}


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/*Declaracion e funciones*/
void func(double *f, double *x, int tamano);
/*Main*/
int main(void)
{
  int i;
  double x_min = 0.0;
  double x_max = 1.0;
  double y_min = 0.0;
  double y_max = 1.0;
  int puntos = 15000;
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
  /*Se implementa el metodo de Monte Carlo*/
  double puntos_debajo = 0.0;
  double area_cuadrado = (x_max-x_min)*(y_max-y_min);
  for(i=0;i<puntos;i++){
    double x_sample = drand48();
    if(exp(-x_sample)< y[i]){
      puntos_debajo += 1.0;
    }
  }
  double integral = area_cuadrado * (puntos_debajo/puntos);
  printf("El valor de la integral es: %f", integral);
  return 0;
}
/*Funcion que calcula exp(-x)*/
void func(double *f, double *x, int tamano)
{
  int i;
  for(i=0;i<tamano;i++) {
    f[i] = exp(-x[i]);
    }
}



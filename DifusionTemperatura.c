#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{
  /*Parametros del problema*/
    int longitud_placa = 100; /*cm*/
    int dx = 1; /*cm*/
    int num_filas = longitud_placa/dx;/*Que en este caso es igual al numero de columnas*/
    float nu = 1/1000; /*coeficiente*/
    float dt = 0.1*(dx*dx)/nu; 
    float r = nu*dt/(dx*dx);
    float temp_inicial = 50.0;
    float temp_rectangulo = 100.0;
    /*Arrays en 2D de la temperatura de la placa*/
    int i;
    /*Inicial*/
    float **T_inicial;
    T_inicial = malloc(num_filas*sizeof(int*));
    for(i=0,i<num_filas,i++){
        T_inicial[i] = malloc(num_filas*sizeof(int));
    }
    /*Presente*/
    float **T_present;
    T_present = malloc(num_filas*sizeof(int*));
    for(i=0,i<num_filas,i++){
        T_present[i] = malloc(num_filas*sizeof(int));
    }
    /*Futuro*/
    float **T_future;
    T_future = malloc(num_filas*sizeof(int*));
    for(i=0,i<num_filas,i++){
        T_future[i] = malloc(num_filas*sizeof(int));
    }
    
    /*Se inicializa la tempertura inicial en todos los puntos de la placa*/
    inicializar(T_inicial, temp_inicial, temp_tectangulo);
    imprimir(T_inicial, num_filas, dt);
    return 0;
}
/*Funcion de incializacion de temperatura*/
void inicializar(FLOAT **T_inicial, FLOAT temp_inicial, FLOAT temp_rectangulo)
{
    int i,j;
    for(i=1,i<(rows-1),i++){
        for(j=1,j<(cols-1),j++){
            if((i<19 || i>29) && (j<39 || j>59)){
	      T_inicial[i][j] = temp_inicial;
            }else{
                T_inicial[i][j] = t_rectangulo;
            }
        }
    }
}
/*Funcion de prueba. Imprime en la consola lo que ingresa por parametro*/
void imprimir(float **array, int tamano_array, float constante)
{
  int i;
  printf("Valor de la constante: %f\n", constante);
  for(i=0,i<tamano_array,i++){
    for(j=0,j<tamano_array,j++){
       printf(%f, array[i][j]);
    }
    printf(\n);
  }
}
/*****Caso 1*****/
/*Funcion para condiciones de frontera periodicas*/
void iteracion_period(FLOAT **T_present, FLOAT **T_future, FLOAT r, int rows, int cols)
{
    int i,j;
    for(i=1,i<(rows-1),i++){
        for(j=1,j<(cols-1),j++){
            T_future[i][j] = T_present[i][j] + r*(T_present[i][j+1]-2*T_present[i][j]+T_present[i][j-1]) + r*(T_present[i+1][j] - 2*T_present[i][j]+T_present[i-1][j]);
        }
    }
    /*Condiciones de frontera*/
    /*Primera fila*/
    for(j=0,j<cols,j++){
        if(j == 0){
            T_future[0][j] = T_present[0][j] + r*(T_present[0][j+1]-2*T_present[0][j]+T_present[0][cols-1]) + r*(T_present[1][j] - 2*T_present[0][j]+T_present[rows-1][j]);
        }
        else{
            T_future[0][j] = T_present[0][j] + r*(T_present[0][j+1]-2*T_present[0][j]+T_present[0][j-1]) + r*(T_present[1][j] - 2*T_present[0][j]+T_present[rows-1][j]);
        }
    }
    /*Primera columna*/
    for(i=0,i<cols,i++){
        if(i == 0){
          T_future[i][0] = T_present[i][0] + r*(T_present[i][1]-2*T_present[i][0]+T_present[i][cols-1]) + r*(T_present[i+1][j] - 2*T_present[i][0]+T_present[rows-1][0]);  
        }
        else{
            T_future[i][0] = T_present[i][0] + r*(T_present[i][1]-2*T_present[i][0]+T_present[i][cols-1]) + r*(T_present[i+1][j] - 2*T_present[i][0]+T_present[i-1][0]);
        }
    }
    /*Ultima fila*/
    for(j=1,j<cols,j++){
        T_future[rows-1][j] = T_present[rows-1][j] + r*(T_present[rows-1][j+1]-2*T_present[rows-1][j]+T_present[rows-1][j-1]) + r*(T_present[0][j]-2*T_present[rows-1][j]+T_present[rows-2][j]);
    }
    /*Ultima columna*/
    for(i=1,i<rows,i++){
        T_future[i][cols-1] = T_present[i][cols-1] + r*(T_present[i][0]-2*T_present[i][cols-1]+T_present[i][cols-2]) + r*(T_present[0][cols-1] - 2*T_present[i][cols-1]+T_present[i-1][cols-1]);
    }
}
/*Funcion para condiciones de frontera fijas*/
void iteracion_fijas(FLOAT **T_present, FLOAT **T_future, FLOAT r, int rows, int cols)
{
    int i,j;
    for(i=1,i<(rows-1),i++){
        for(j=1,j<(cols-1),j++){
            T_future[i][j] = T_present[i][j] + r*(T_present[i][j+1]-2*T_present[i][j]+T_present[i][j-1]) + r*(T_present[i+1][j] - 2*T_present[i][j]+T_present[i-1][j]);
        }
    }
    /*Condiciones de frontera*/
   for(j=0,j<cols,j++){/*Primera fila*/
       T_future[0][j] = 50;
   }
   for(i=0,i<rows,i++){/*Primera columna*/
       T_future[i][j] = 50;
   }
   for(j=1,j<cols,j++){/*Ultima fila*/
       T_future[rows-1][j] = 50;
   }
   for(i=1,i<rows,i++){/*Ultima columna*/
       T_future[i][cols-1] = 50;
   }
}
/*****Caso 2*****/
/*Funcion para condiciones de frontera periodicas con fuente de calor*/
void iteracion_period_CALOR(FLOAT **T_present, FLOAT **T_future, FLOAT r, int rows, int cols, FLOAT t_constante)
{
    int i,j;
    for(i=1,i<(rows-1),i++){
        for(j=1,j<(cols-1),j++){
            if((i<19 || i>29) && (j<39 || j>59)){
            T_future[i][j] = T_present[i][j] + r*(T_present[i][j+1]-2*T_present[i][j]+T_present[i][j-1]) + r*(T_present[i+1][j] - 2*T_present[i][j]+T_present[i-1][j]);
            }else{
                T_future[i][j] = t_constante;
            }
        }
    }
    /*Condiciones de frontera*/
    /*Primera fila*/
    for(j=0,j<cols,j++){
        if(j == 0){
            T_future[0][j] = T_present[0][j] + r*(T_present[0][j+1]-2*T_present[0][j]+T_present[0][cols-1]) + r*(T_present[1][j] - 2*T_present[0][j]+T_present[rows-1][j]);
        }
        else{
            T_future[0][j] = T_present[0][j] + r*(T_present[0][j+1]-2*T_present[0][j]+T_present[0][j-1]) + r*(T_present[1][j] - 2*T_present[0][j]+T_present[rows-1][j]);
        }
    }
    /*Primera columna*/
    for(i=0,i<cols,i++){
        if(i == 0){
          T_future[i][0] = T_present[i][0] + r*(T_present[i][1]-2*T_present[i][0]+T_present[i][cols-1]) + r*(T_present[i+1][j] - 2*T_present[i][0]+T_present[rows-1][0]);  
        }
        else{
            T_future[i][0] = T_present[i][0] + r*(T_present[i][1]-2*T_present[i][0]+T_present[i][cols-1]) + r*(T_present[i+1][j] - 2*T_present[i][0]+T_present[i-1][0]);
        }
    }
    /*Ultima fila*/
    for(j=1,j<cols,j++){
        T_future[rows-1][j] = T_present[rows-1][j] + r*(T_present[rows-1][j+1]-2*T_present[rows-1][j]+T_present[rows-1][j-1]) + r*(T_present[0][j]-2*T_present[rows-1][j]+T_present[rows-2][j]);
    }
    /*Ultima columna*/
    for(i=1,i<rows,i++){
        T_future[i][cols-1] = T_present[i][cols-1] + r*(T_present[i][0]-2*T_present[i][cols-1]+T_present[i][cols-2]) + r*(T_present[0][cols-1] - 2*T_present[i][cols-1]+T_present[i-1][cols-1]);
    }
}
/*Funcion para condiciones de frontera fijas con fuente de calor*/
void iteracion_fijas_CALOR(FLOAT **T_present, FLOAT **T_future, FLOAT r, int rows, int cols, FLOAT t_constante)
{
    int i,j;
    for(i=1,i<(rows-1),i++){
        for(j=1,j<(cols-1),j++){
            if((i<19 || i>29) && (j<39 || j>59)){
            T_future[i][j] = T_present[i][j] + r*(T_present[i][j+1]-2*T_present[i][j]+T_present[i][j-1]) + r*(T_present[i+1][j] - 2*T_present[i][j]+T_present[i-1][j]);
            }else{
                T_future[i][j] = t_constante;
            }
        }
    }
    /*Condiciones de frontera*/
   for(j=0,j<cols,j++){/*Primera fila*/
       T_future[0][j] = 50;
   }
   for(i=0,i<rows,i++){/*Primera columna*/
       T_future[i][j] = 50;
   }
   for(j=1,j<cols,j++){/*Ultima fila*/
       T_future[rows-1][j] = 50;
   }
   for(i=1,i<rows,i++){/*Ultima columna*/
       T_future[i][cols-1] = 50;
   }
}                                                                                                                
                                 
                                                                                                                              
                                                                                                                              
                                                                                                                              
                                                                                                                              
                                                                                                                              
                                                                                                                              
                                                                                                                              
                                                                                                                              
                                                                                                                              
                                                                                                                              
                                                                                                                              
                                                                                                                              
                                                                                                                              
                                                                                                                              
                                                                                                                              
                                                                                                                              
                                                                                                                              
                                                                                                                              
                                                                                                                              
                                                                                                                              
                                                                                                                              

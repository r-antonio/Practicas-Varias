#include<stdio.h>
#include<stdlib.h>
#include<math.h>

//Dimension por defecto de las matrices
int N=100;
int m=4;

//Para calcular tiempo
double dwalltime(){
        double sec;
        struct timeval tv;

        gettimeofday(&tv,NULL);
        sec = tv.tv_sec + tv.tv_usec/1000000.0;
        return sec;
}

int main(int argc,char*argv[]){
 double *R;
 int i,j,k,c;
 int check=1;
 double max,min,avg,escalar,temp;
 double timetick;

 //Controla los argumentos al programa
 if ((argc != 3) || ((N = atoi(argv[1])) <= 0) || ((m = atoi(argv[2])) <= 0))
  {
    printf("\nUsar: %s n m\n  n: Dimension de la matriz (nxn X nxn)\n  m: Cantidad de matrices\n", argv[0]);
    exit(1);
  }

 //Aloca memoria para las matrices
  R=(double*)malloc(sizeof(double)*N*N);

  double** M;
  M = (double**)malloc(sizeof(double*)*m);
  for(i=0;i<m;i++){
    M[i]=(double*)malloc(sizeof(double)*N*N);
  }
 //Inicializa las matrices
 for(k=0;k<m;++k){
   for(i=0;i<N;++i){
     for(j=0;j<N;++j){
       M[k][i*N+j] = (double) (rand() % 1000000000);
     }
   }
 }

 //Realiza la multiplicacion

  timetick = dwalltime();

  int cantElem=N*N*m;

//calculo de matrices
  min=999999999;
  max=-1;
  avg=0;

//productoria
  
  for(i=0;i<N;++i){
    for(j=0;j<N;++j){
      R[i*N+j]=0;
      if(M[0][i*N+j] < min) min=M[0][i*N+j];
      if(M[0][i*N+j] > max) max=M[0][i*N+j];
      if(M[1][i*N+j] < min) min=M[1][i*N+j];
      if(M[1][i*N+j] > max) max=M[1][i*N+j];
      avg+=M[0][i*N+j]+M[1][i*N+j];
      for(c=0;c<N;++c){
        R[i*N+j]+=M[0][i*N+c]*M[1][c+j*N];
      }
    }
  }
  
  for(k=2;k<m;++k){
    if(k%2==1){
      for(i=0;i<N;++i){
        for(j=0;j<N;++j){
          R[i*N+j]=0;
          if(M[k][i*N+j] < min) min=M[k][i*N+j];
          if(M[k][i*N+j] > max) max=M[k][i*N+j];
          avg+=M[k][i*N+j];
          for(c=0;c<N;++c){
            R[i*N+j]+=M[0][i*N+c]*M[k][c+j*N];
          }
        }
      }
    } else {
      for(i=0;i<N;++i){
        for(j=0;j<N;++j){
          M[0][i*N+j]=0;
          if(M[k][i*N+j] < min) min=M[k][i*N+j];
          if(M[k][i*N+j] > max) max=M[k][i*N+j];
          avg+=M[k][i*N+j];
          for(c=0;c<N;++c){
            M[0][i*N+j]+=R[i*N+c]*M[k][c+j*N];
          }
        }
      }
    }
  }

//if m es par el resultado esta en M[0] sino en R   
  if(m%2 == 1){
    free(R);
    R=M[0];
  }
//multiplicacion del resultado por el escalar elevado a la m
  avg/=cantElem;
  escalar=pow(((max-min)/avg),m);
  for(i=0;i<N;++i){
    for(j=0;j<N;++j){
      R[i*N+j] *= escalar;
    }
  }

 printf("Tiempo en segundos %f\n", dwalltime() - timetick);

  free(R);
  for(i=1;i<m;++i){
    free(M[i]);
  }
  free(M);

 return(0);
}


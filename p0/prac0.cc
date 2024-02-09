// Práctica 0
#include <iostream>
#include <string.h>

using namespace std;

//EJERCICIO 1
bool multiple(int numA, int numB){

  if(numA%numB == 0 || numB%numA == 0){
    cout << "True" << endl;
    return true;
  }
  else{
    cout << "False" << endl;
    return false;
  }
}

//EJERCICIO 2
int printN(int tamanyo){
  int contadorAs = 0, aux1, aux2;
  
  cout << endl;
    if(tamanyo >= 4) {
      for(aux1 = 0; aux1 < tamanyo; aux1++){
        for(aux2 = 0; aux2 < tamanyo; aux2++){
          if(aux2 == 0||aux2 == tamanyo-1||aux2==aux1){
            cout<<"*";
            contadorAs ++;
          }
          else{
            cout<<" ";
          }
        }
        cout << endl;
      }
    }
    else{
      cout << "ERROR" << endl;
    }

  return contadorAs;
}


//EJERCICIO 3
bool isPrime(int contador){
  int auxi;

  if(contador <= 1){
    return false;
  }
  for(auxi = 2; auxi <= contador/2; auxi++){
    if(contador % auxi == 0){
      return false;
    }
  }

  return true;
}

int firstPrimes(int num){
  int cantidad = 0, contador, sumador = 0;
  
  cout << endl;
  for(contador = 2 ; cantidad < num; contador++){
    if(isPrime(contador)){
      cout << contador << " ";
      sumador = sumador + contador;
      cantidad++;
    }
  }
  
  return sumador;
}

//EJERCICIO 4
void Goldbach(int nume,int *pri1,int *pri2){
  int n1, n2, auxi = 0;

    for(n1 = 0; (n1 < nume) && (auxi == 0); n1++){
      for(n2 = 0; (n2 < nume) && (auxi == 0); n2++){
        if(isPrime(n1) && isPrime(n2)){
          if(n1+n2 == nume){
            if(n1 < n2){
              *pri1 = n1;
              *pri2 = n2;
            }
            else{
              *pri1 = n2;
              *pri2 = n1;
            }
            auxi++;
          }
        }
      }
    }
}

//EJERCICIO 5
bool search(int v[], const int TAMVECTOR, int n){
  int buscador;

  for(buscador = 0; buscador < TAMVECTOR; buscador++){
    if(v[buscador] == n){
      return true;
    }
  }
  return false;
}

int position(int v[],const int TAMVECTOR, int n){
  int posicion;

  for(posicion = 0; posicion < TAMVECTOR; posicion++){
    if(v[posicion] == n){
      return posicion;
    }
  }
  return -1;
}

int count(int v[], const int TAMVECTOR, int n) {
  int auxi, contador = 0;

  for (auxi = 0; auxi < TAMVECTOR; auxi++) {
    if (v[auxi] == n) {
      contador++;
    }
  }

  return contador;
}


//EJERCICIO 6
int minOdds(int v[],const int TAMVECTOR){
  int auxi, contImpar = 0;

  for(auxi = 0; auxi < TAMVECTOR; auxi++){
    if(v[auxi] % 2 != 0){
      contImpar ++;
    }
  }
 
  if(contImpar == 0){
    return -1;
  }

  return contImpar;
}

int posMaxMultFive(int v[],const int TAMVECTOR){
  int auxi, posMax = -1, valMax = 0;

  for(auxi = 0; auxi < TAMVECTOR; auxi++){
    if(v[auxi] % 5 == 0 || v[auxi] == 0){
      if(v[auxi] > valMax){
          posMax = auxi;
          valMax = v[auxi];
      }
    }
  } 
    return posMax;
}


//EJERCICIO 7
void deleteChar(char str[],char c){
  int auxi, largo = strlen(str), contador = 0;

  for(auxi = 0; auxi < largo; auxi++){
    if(str[auxi] != c){
      str[contador++] = str[auxi];
    }
  }
  str[contador] = '\0';
}

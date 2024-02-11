// Programación 2 - Práctica 0
// DNI: A8590323
// Nombre: Roberto Loor

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
  int contadorAs = 0, auxN1, auxN2;
  
  cout << endl;
    if(tamanyo >= 4) {
      for(auxN1 = 0; auxN1 < tamanyo; auxN1++){
        for(auxN2 = 0; auxN2 < tamanyo; auxN2++){
          if(auxN2 == 0||auxN2 == tamanyo-1||auxN2==auxN1){
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
  int comprobador;

  if(contador <= 1){
    return false;
  }
  for(comprobador = 2; comprobador <= contador/2; comprobador++){
    if(contador % comprobador == 0){
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
void Goldbach(int nume,int &pri1,int &pri2){
  int n1, n2, auxiSalida = 0;

    for(n1 = 1; (n1 < nume) && (auxiSalida == 0); n1++){
      for(n2 = 1; (n2 < nume) && (auxiSalida == 0); n2++){
        if(isPrime(n1) && isPrime(n2)){
          if(n1+n2 == nume){
            if(n1 < n2){
              pri1 = n1;
              pri2 = n2;
            }
            else{
              pri1 = n2;
              pri2 = n1;
            }
            auxiSalida++;
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
      cout << "True" << endl;
      return true;
    }
  }
  cout << "False" << endl;
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
  int comprobador, contador = 0;

  for (comprobador = 0; comprobador < TAMVECTOR; comprobador++) {
    if (v[comprobador] == n) {
      contador++;
    }
  }

  return contador;
}


//EJERCICIO 6
int minOdds(int v[],const int TAMVECTOR){
  int buscador, minImpar = 0;

  for(buscador = 0; buscador < TAMVECTOR; buscador++){
    if(v[buscador] % 2 != 0 && minImpar == 0){
      minImpar = v[buscador];
    }
    else if(v[buscador] % 2 != 0 && v[buscador] < minImpar){
      minImpar = v[buscador];
    }
  }

  return minImpar;
}


int posMaxMultFive(int v[],const int TAMVECTOR){
  int buscador, posMax = -1, valMax = 0;

  for(buscador = 0; buscador < TAMVECTOR; buscador++){
    if(v[buscador] % 5 == 0 || v[buscador] == 0){
      if(v[buscador] > valMax){
          posMax = buscador;
          valMax = v[buscador];
      }
    }
  } 
  
    return posMax;
}


//EJERCICIO 7
void deleteChar(char str[],char c){
    int buscador, largo = strlen(str), pos = 0;

    for(buscador = 0; buscador < largo; buscador++){
    if(str[buscador] != c){
      str[pos] = str[buscador];
      pos++;
    }
  }
    str[pos] = '\0';
}

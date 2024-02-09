// Práctica 0
#include <iostream>

using namespace std;

////EJERCICIO 1
bool multiple(int numA, int numB){
  do{
    cout << "Introduzca dos numeros separados por un espacio" << endl;
    cin >> numA >> numB;
  } while (numA == 0 || numB == 0);

  if(numA%numB == 0 || numB%numA == 0){
    return true;
  }
  else{
    return false;
  }
  
}

//EJERCICIO 2
int printN(int tamanyo){
  int contadorAs = 0;
    cout << "Introduzca un numero" << endl;
    cin >> tamanyo;

    if(tamanyo >= 4) {
      for(int aux1 = 0; aux1 < tamanyo; aux1++){
        for(int aux2 = 0; aux2 < tamanyo; aux2++){
          if(aux2 == 0||aux2 == tamanyo-1||aux2==aux1){
            cout<<"*";
            contadorAs ++;
          }
          else{
            cout<<" ";
          }
        cout << endl;
        }
      }
    }
    else{
      cout << "ERROR" << endl;
    }

  cout << "La cantidad de asteriscos es:" << contadorAs << endl;
  
  return contadorAs;
}


//EJERCICIO 3
int firstPrimes(int nume){
  int cantidad = 0, contador, sumador = 0;

  for(contador = 2 ; cantidad < nume; contador++){
    if(isPrime(contador)){
      cout << contador << " ";
      sumador = sumador + contador;
        cantidad++;
    }
  }
  cout << endl;
  cout << "La suma de los numeros es " << sumador << endl;
  return sumador;
}


bool isPrime(int contador){
  int auxi2;

  if(contador <= 1){
    return false;
  }
  for(auxi2 = 2; auxi2 <= contador/2; auxi2++){
    if(contador % auxi2 == 0){
      return false;
    }
  }
  return true;
}


//EJERCICIO 4
void Goldbach(int nume,int *pri1,int *pri2){








}

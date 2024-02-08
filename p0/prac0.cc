
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
            contador ++;
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
int firstPrimes(int n);
bool isPrime(int p);



int firstPrimes(int cantidad){
  int auxi, sumador = 0;

    cout << "Introduzca un numero" << endl;
    cin >> cantidad;

  for(auxi = 2 ; cantidad != contador; auxi++){
    if(isPrime(auxi)){
      cout << auxi << " ";
      sumador = sumador + auxi;
  }





bool isPrime(int auxi){
  if(auxi > 1 &&
  
}


#ifndef _SNFOLLOWERS_H_ // Si no está definido el _SNFOLLOWERS_H_
#define _SNFOLLOWERS_H_ // Definir _SNFOLLOWERS_H_
#include <iostream> 
#include <vector>
#include "Util.h" // Incluir Util.h que es una clase

using namespace std;

class SNFollowers{
    // Funciones amigas
    friend ostream& operator<<(ostream& os, const SNFollowers& snf); // Función que imprime la clase
    // Atributos y métodos
    private:
        string name; // Nombre de la red social
        int numFollowers; // Número de seguidores de la red social
        double money; // Cantidad de dinero de la red social
    public:
        SNFollowers(string name, int initialFollowers); // Constructor de la clase
        void addFollowers(int nf); // Agrega seguidores a la red social
        void addEvent(double rating); // Agrega un evento a la red social
        double collectCommission(double commission); // Recolecta la comisión de la red social
        string getName() const {return name;} // Devuelve el nombre de la red social
        int getNumFollowers() const {return numFollowers;} // Devuelve el número de seguidores de la red social
        double getMoney() const {return money;} // Devuelve la cantidad de dinero de la red social
};

#endif // Fin del if

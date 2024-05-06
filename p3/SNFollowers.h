#ifndef _SNFOLLOWERS_H_
#define _SNFOLLOWERS_H_
#include <iostream>
#include <vector>
#include "Util.h"

using namespace std;

class SNFollowers{
    //AMIGAS
    friend ostream& operator<<(ostream& os, const SNFollowers& snf); // Función que imprime la clase
    //ATRIBUTOS Y METODOS
    private:
        string name;
        int numFollowers;
        double money;
    public:
        SNFollowers(string name, int initialFollowers); // Constructor de la clase
        void addFollowers(int nf); // Agrega seguidores a la red social
        void addEvent(double rating); // Agrega un evento a la red social
        double collectCommission(double commission); // Recolecta la comisión de la red social
        string getName() const {return name;} // Devuelve el nombre de la red social
        int getNumFollowers() const {return numFollowers;} // Devuelve el número de seguidores de la red social
        double getMoney() const {return money;} // Devuelve la cantidad de dinero de la red social
};

#endif

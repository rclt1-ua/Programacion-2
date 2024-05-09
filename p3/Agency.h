#ifndef _AGENCY_H // Si no está definido el _AGENCY_H
#define _AGENCY_H // Definir _AGENCY_H
#include <iostream> 
#include <vector> 
#include "Util.h" // Incluir Util.h que es una clase
#include "Influencer.h" // Incluir Influencer.h que es una clase

using namespace std;

class Agency{
    //Funciones amigas
    friend ostream& operator<<(ostream& os, const Agency& agency); // Función que imprime la clase
    //Atributos y métodos
    private:
        string name; // Nombre de la agencia
        double money; // Cantidad de dinero de la agencia
        vector<Influencer> influencers; // Los influencers que son parte de la agencia
    public:
        Agency(string name, double initialMoney); // Constructor de la clase
        Influencer *searchInfluencer(string infName); // Busca un influencer en la lista de influencers
        void addInfluencer(string infName, double commission);// Agrega un influencer a la lista de influencers
        void addFollowers(string infName, string snName, int nFollowers); // Agrega seguidores a un influencer 
        void newEvent(vector<string> infNames, int nsns, string snNames[], double evtRatings[]); // Crea un nuevo evento
        void deleteInfluencer(string infName); // Elimina un influencer de la lista de influencers
        double collectCommissions(); // Recolecta las comisiones de los influencers
        string getName() const {return name;} // Devuelve el nombre de la agencia
        double getMoney() const {return money;} // Devuelve la cantidad de dinero de la agencia
};

#endif // Fin del if 






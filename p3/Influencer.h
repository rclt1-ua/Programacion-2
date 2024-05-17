#ifndef _INFLUENCER_H // Si no está definido el _INFLUENCER_H
#define _INFLUENCER_H // Definir _INFLUENCER_H
#include <iostream>
#include <vector>
#include "SNFollowers.h" // Incluir SNFollowers.h que es una clase
#include "Util.h" // Incluir Util.h que es una clase

using namespace std;

class Influencer{ // Clase Influencer
    //Funciones amigas
    friend ostream & operator<<(ostream &os, const Influencer &influencer); // Función que imprime la clase
    //Atributos y métodos
    private:
        vector<SNFollowers> followers; // Lista de seguidores
        string name; // Nombre del influencer
        double commission; // Comisión del influencer
    public:
        Influencer(string name); // Constructor de la clase
        void setCommission(double commission); // Establece la comisión
        void addFollowers(string snName,int nFollowers); // Agrega seguidores
        void addEvent(int nsns,string sn[],double rat[]); // Agrega un evento
        double collectCommission(); // Recolecta la comisión
        string getName() const {return name;} // Devuelve el nombre del influencer
        vector<SNFollowers> getFollowers() const {return followers;} // Devuelve los seguidores del influencer
        double getCommission() const {return commission;} // Devuelve la comisión del influencer
};

#endif // Fin del if
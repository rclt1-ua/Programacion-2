#ifndef _SNDATA_H_ // Si no está definido el _SNDATA_H
#define _SNDATA_H_ // Definir _SNDATA_H
#include <iostream>
#include <vector>
#include "Util.h" // Incluir Util.h que es una clase

using namespace std;

struct SocialNetworkData{ // Estructura de datos de la red social
    string name; // Nombre de la red social
    double averageRating; // Promedio de rating
    double averageMonetizing; // Promedio de monetización
};

class SNData{ // Clase SNData
    //Atributos y métodos
    private:
        static vector<SocialNetworkData> sns; // Vector de datos de la red social
    public:
        static void newSocialNetwork(string name, double avgR, double avgM); // Crea una nueva red social
        static bool checkSN(string name); // Revisa si la red social existe
        static double getAvgRating(string name); // Obtiene el promedio de rating de la red social
        static double getAvgMonetizing(string name); // Obtiene el promedio de monetización de la red social
};

#endif // Fin de _SNDATA_H_
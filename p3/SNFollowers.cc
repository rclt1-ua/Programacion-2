#include "SNFollowers.h"
#include "SNData.h"

SNFollowers::SNFollowers(string name, int initialFollowers){
    SNData sn;
    if(!sn.checkSN(name)){throw EXCEPTION_UNKNOWN_SN;} //Si la red social no existe, lanza excepcion
    if(initialFollowers < 0){throw invalid_argument(to_string(initialFollowers));} //Si la cantidad de seguidores es menor a 0, lanza excepcion
    this->name = name; //El nombre de la red social es el nombre que se le pasa
    numFollowers = initialFollowers; // La cantidad de seguidores es la cantidad que se le pasa
    money = 0.0; // La cantidad de dinero es 0.0
}   

void SNFollowers::addFollowers(int nf){ // Agrega seguidores a la red social
    if(nf < 0){throw invalid_argument(to_string(nf));} // Si la cantidad de seguidores es menor a 0, lanza excepcion
    numFollowers += nf; // La cantidad de seguidores es la cantidad de seguidores que se le pasa
    if(numFollowers < 0){numFollowers = 0;} // Si la cantidad de seguidores es menor a 0, la cantidad de seguidores es 0
}

void SNFollowers::addEvent(double rating){
    SNData sn;
    double avgRating = sn.getAvgRating(name), //Obtiene el promedio de rating de la red social
        avgMonetizing = sn.getAvgMonetizing(name), //Obtiene el promedio de monetización de la red social
        relation = rating / avgRating; //La relación es el rating entre el promedio de rating
    int newFollowers = 0, //La cantidad de seguidores nuevos es 0
        lostFollowers = 0; //La cantidad de seguidores perdidos es 0

    if(rating < 0){throw invalid_argument(to_string(rating));} // Si el rating es menor a 0, lanza excepcion

    if(relation > 0.8){ //Si la relación es mayor a 0.8
        newFollowers = relation * numFollowers; // La cantidad de seguidores nuevos es la relación por la cantidad de seguidores
        numFollowers += newFollowers; // La cantidad de seguidores es la cantidad de seguidores más la cantidad de seguidores nuevos
        money += newFollowers * avgMonetizing; // La cantidad de dinero es la cantidad de dinero más la cantidad de seguidores nuevos por el promedio de monetización
    }
    else{
        lostFollowers = (0.9 - relation) * numFollowers; // La cantidad de seguidores perdidos es 0.9 menos la relación por la cantidad de seguidores
        numFollowers -= lostFollowers; // La cantidad de seguidores es la cantidad de seguidores menos la cantidad de seguidores perdidos
        if(numFollowers < 0){numFollowers = 0;} // Si la cantidad de seguidores es menor a 0, la cantidad de seguidores es 0
    }
}

double SNFollowers::collectCommission(double commission){ // Recolecta la comisión de la red social
    double comissionMoney;
    if(commission <= 0 || commission >= 1){throw invalid_argument(to_string(commission));} // Si la comisión es menor o igual a 0 o mayor o igual a 1, lanza excepcion
    comissionMoney = money * commission; // La cantidad de dinero de la comisión es la cantidad de dinero por la comisión
    money = 0.0; // La cantidad de dinero es 0.0
    return comissionMoney; // Devuelve la cantidad de dinero de la comisión
}

ostream& operator<<(ostream& os, const SNFollowers& snf){ // Función que imprime la clase
    os << "[" << snf.name << "|" << snf.numFollowers << "|" << snf.money << "]"; // Imprime el nombre de la red social, la cantidad de seguidores y la cantidad de dinero
    return os;
}




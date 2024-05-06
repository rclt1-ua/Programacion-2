#include "SNData.h" // Incluir SNData.h que es una clase

vector<SocialNetworkData> SNData::sns;

void SNData::newSocialNetwork(string name, double avgR, double avgM){ // Metodo que crea una nueva red social
    SocialNetworkData sN;
    int recorredor;
    for(recorredor = 0; recorredor < (int)sns.size(); recorredor++){ //Verifica si ya existe la red social
        if(sns[recorredor].name == name){throw invalid_argument(name);}} //Si ya existe, lanza excepcion

    if(avgR <= 0 || avgR >= 1){throw invalid_argument(to_string(avgR));} //Si el promedio de rating es menor o igual a 0 o mayor o igual a 1, lanza excepcion
    if(avgM <= 0 || avgM >= 1){throw invalid_argument(to_string(avgM));} //Si el promedio de monetizacion es menor o igual a 0 o mayor o igual a 1, lanza excepcion
    sN.name = name;
    sN.averageRating = avgR;
    sN.averageMonetizing = avgM;
    sns.push_back(sN); //Agrega la red social
}

bool SNData::checkSN(string name){ // Metodo que verifica si existe una red social
    int recorredor;
    for(recorredor = 0; recorredor < (int)sns.size(); recorredor++){ //Recorre las redes sociales
        if(sns[recorredor].name == name){return true;}}//Si encuentra la red social, devuelvo verdadero
    return false; //Si no la encuentra, devuelve falso
}

double SNData::getAvgRating(string name){ // Metodo que obtiene el promedio de rating de una red social
    int recorredor;
    for(recorredor = 0; recorredor < (int)sns.size(); recorredor++){ //Recorre las redes sociales
        if(sns[recorredor].name == name){return sns[recorredor].averageRating;}} //Si encuentra la red social, devuelvo el promedio de rating
    return 0.0; //Si no la encuentra, devuelvo 0.0
}

double SNData::getAvgMonetizing(string name){ // Metodo que obtiene el promedio de monetizacion de una red social
    int recorredor;
    for(recorredor = 0; recorredor < (int)sns.size(); recorredor++){ //Recorre las redes sociales
        if(sns[recorredor].name == name){return sns[recorredor].averageMonetizing;}} // Si encuentra la red social, devuelvo el promedio de monetizacion
    return 0.0; //Si no la encuentra, devuelvo 0.0
}
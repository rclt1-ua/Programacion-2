#include "Influencer.h" // Incluir Influencer.h que es una clase

Influencer::Influencer(string name){ // Constructor de la clase
    this->name = name; // El nombre del influencer es el nombre que se le pasa
    this->commission = 0.1; // La comisión del influencer inicialmente es 0.1
}

void Influencer::setCommission(double commission){ // Establece la comisión
    if(commission > 0 && commission < 0.8){ // Si la comisión es mayor a 0 y menor a 0.8
        this->commission = commission; // La comisión del influencer es la comisión que se le pasa
    }else{throw EXCEPTION_WRONG_COMMISSION;} // Si no, lanza una excepción de comisión incorrecta
}

void Influencer::addFollowers(string snName,int nFollowers){ // Agrega seguidores
    int recorredor;
    for(recorredor = 0; recorredor < (int)followers.size(); recorredor++){ // Recorre la lista de seguidores
        if(followers[recorredor].getName() == snName){ // Si el seguidor es igual al seguidor buscado
            followers[recorredor].addFollowers(nFollowers); // Agrega seguidores al seguidor
            return;
        }       
    }
    try{
        SNFollowers snf(snName,nFollowers); // Crea un nuevo seguidor
        followers.push_back(snf); // Agrega el seguidor a la lista de seguidores
    }catch(Exception &e){
        Util::error(ERR_UNKNOWN_SN);} // Si no se puede crear el seguidor, imprime un error de red social desconocida
}

void Influencer::addEvent(int nsns,string sn[],double rat[]){// Agrega un evento
    int recorredor;
    for(recorredor = 0; recorredor < nsns; recorredor++){ // Recorre la lista de seguidores
        int recorredor2;
        for(recorredor2 = 0; recorredor2 < (int)followers.size(); recorredor2++){ // Recorre la lista de seguidores
            if(followers[recorredor2].getName() == sn[recorredor]){ // Si el seguidor es igual al seguidor buscado
                followers[recorredor2].addEvent(rat[recorredor]); // Agrega el evento al seguidor
            }
        }
    }
}

double Influencer::collectCommission(){ // Recolecta la comisión
    double comision = 0;
    int recorredor; 
    for(recorredor = 0; recorredor < (int)followers.size(); recorredor++){ // Recorre la lista de seguidores
        comision += followers[recorredor].collectCommission(commission); // Recolecta la comisión de los seguidores
    }
    return comision; // Devuelve la comisión
} 

ostream & operator<<(ostream& os, const Influencer &influencer){ // Función que imprime la clase
    int recorredor;
    os << "Influencer: " << influencer.name << " (" << influencer.commission << ")" << endl;
    for(recorredor = 0; recorredor < (int)influencer.followers.size(); recorredor++){ // Recorre la lista de seguidores
        os << influencer.followers[recorredor]; // Imprime los seguidores
    }
    cout << endl; // Salto de línea
    return os;
}


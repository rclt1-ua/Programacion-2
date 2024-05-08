#include "Agency.h" // Incluir Agency.h que es una clase

Agency::Agency(string name, double initialMoney){ // Constructor de la clase
    this->name = name; // El nombre de la agencia es el nombre que se le pasa
    this->money = initialMoney; // La cantidad de dinero de la agencia es la cantidad de dinero que se le pasa
}

Influencer *Agency::searchInfluencer(string infName){ // Busca un influencer en la lista de influencers
    int recorredor;
    for (recorredor = 0; recorredor < (int)influencers.size(); recorredor++){ // Recorre la lista de influencers
        if (influencers[recorredor]->getName() == infName){ // Si el influencer es igual al influencer buscado
            return influencers[recorredor]; // Devuelve el influencer
        }
    }
    throw EXCEPTION_INFL_NOT_FOUND; // Si no, lanza una excepción de influencer no encontrado
}

void Agency::addInfluencer(string infName, double commission){ // Agrega un influencer a la lista de influencers
    try{ // Intenta ver si el influencer ya existe
        searchInfluencer(infName); // Busca el influencer
        Util::error(ERR_DUPLICATED); // Si lo encuentra, lanza una excepción de duplicado
    }catch(Exception &e){ // Si no lo encuentra
        if (e == EXCEPTION_INFL_NOT_FOUND){ // Si la excepción es de influencer no encontrado
            try{ // Intenta ver si la comisión es correcta
                Influencer *inf = new Influencer(infName); // Crea un nuevo influencer
                inf->setCommission(commission); // Establece la comisión del influencer
                influencers.push_back(inf); // Agrega el influencer a la lista de influencers
            }catch(Exception &e){ // Si no es correcta la comisión
                Util::error(ERR_WRONG_COMMISSION); // Lanza una excepción de comisión incorrecta
            }
        }
    }
}

void Agency::addFollowers(string infName, string snName, int nFollowers){ // Agrega seguidores a un influencer
    try{ // Intenta ver si el influencer existe
        Influencer *inf = searchInfluencer(infName); // Busca el influencers
        inf->addFollowers(snName, nFollowers); // Agrega seguidores al influencers
    }catch(Exception &e){ // Si no lo encuentra
        Util::error(ERR_NOT_FOUND); // Lanza una excepción de no encontrado
    }
}

void Agency::newEvent(vector<string> infNames, int nsns, string snNames[], double evRats[]){ // Crea un nuevo evento
    int recorredor;
    for(recorredor = 0; recorredor < (int)infNames.size(); recorredor++){ // Recorre la lista de influencers
        try{ // Intenta ver si el influencer existe
            Influencer *inf = searchInfluencer(infNames[recorredor]); // Busca el influencer
            inf->addEvent(nsns, snNames, evRats); // Agrega el evento al influencer
        }catch(Exception &e){ // Si no lo encuentra
        // No hace nada
        }
    }
}

void Agency::deleteInfluencer(string infName){ // Elimina un influencer de la lista de influencers
    int recorredor;
    try{
        Influencer *inf = searchInfluencer(infName); // Busca el influencer
        money += inf->collectCommission(); // Recolecta la comisión del influencer
        for (recorredor = 0; recorredor < (int)influencers.size(); recorredor++){ // Recorre la lista de influencers
            if (influencers[recorredor]->getName() == infName){ // Si el influencer es igual al influencer buscado
                influencers.erase(influencers.begin() + recorredor); // Elimina el influencer de la lista de influencers
                return;
            }
        }
    }catch(Exception &e){ // Si no lo encuentra
        cout << ERR_NOT_FOUND; // Lanza una excepción de no encontrado
    }
}

double Agency::collectCommissions(){ // Recolecta las comisiones de los influencers
    double comision = 0;
    int recorredor;
    for (recorredor = 0; recorredor < (int)influencers.size(); recorredor++){ // Recorre la lista de influencers
        comision += influencers[recorredor]->collectCommission(); // Recolecta la comisión de los influencers
    }
    money += comision; // La cantidad de dinero de la agencia es la comisión recolectada
    return comision; // Devuelve la comisión
}

ostream& operator<<(ostream &os, const Agency &agency){ // Función que imprime la clase
    int recorredor;
    os << "Agency: " << agency.name << " [" << agency.money << "]" << endl; // Imprime el nombre de la agencia y la cantidad de dinero
    for (recorredor = 0; recorredor < (int)agency.influencers.size(); recorredor++){ // Recorre la lista de influencers
        os << *agency.influencers[recorredor]; // Imprime los influencers
    }
    cout << endl; // Salto de línea
    return os; // Devuelve la impresión
}


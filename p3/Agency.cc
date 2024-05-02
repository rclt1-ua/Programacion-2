#include "Agency.h"
#include "Influencer.h"
#include "Util.h"

Agency::Agency(string name, double initialMoney){
    this->name = name;
    this->money = initialMoney;
}

Influencer * Agency::searchInfluencer(string infName){
    int recorredor;
    for(recorredor = 0; recorredor < influencers.size(); recorredor++){
        if(influencers[recorredor].getName() == infName){
            return &influencers[recorredor];
        }
    }
    throw EXCEPTION_INFL_NOT_FOUND;
}

void Agency::addInfluencer(string infName, double commission){
    try{
        Influencer * inf = searchInfluencer(infName);
        throw ERR_DUPLICATED;
    }catch(exception &e){
        try{
            Influencer inf(infName);
            inf.setCommission(commission);
            influencers.push_back(inf);
        }catch(exception &e){cout << ERR_WRONG_COMMISSION << endl;}
    }
}

void Agency::addFollowers(string infName, string snName, int nFollowers){
    try{
        Influencer * inf = searchInfluencer(infName);
        inf->addFollowers(snName,nFollowers);
    }catch(exception &e){
        cout << ERR_NOT_FOUND << endl;
    }
}

void Agency::newEvent(vector<string> infNames, int nsns, string snNames[], double evRats[]){
    int recorredor;
    for(recorredor = 0; recorredor < infNames.size(); recorredor++){
        try{
            Influencer * inf = searchInfluencer(infNames[recorredor]);
            inf->addEvent(nsns,snNames,evRats);
        }catch(exception &e){}
    }
}

void Agency::deleteInfluencer(string infName){
    int recorredor;
    for(recorredor = 0; recorredor < influencers.size(); recorredor++){
        if(influencers[recorredor].getName() == infName){
            money += influencers[recorredor].collectCommission();
            influencers.erase(influencers.begin() + recorredor);
            return;
        }
    }
    throw ERR_NOT_FOUND;
}

double Agency::collectCommissions(){
    double comisionRec = 0;
    int recorredor;
    for(recorredor = 0; recorredor < influencers.size(); recorredor++){
        comisionRec += influencers[recorredor].collectCommission();
    }
    money += comisionRec;
    return comisionRec;
}

ostream & operator<<(ostream &os, const Agency &agency){
    os << "Agency: " << agency.name << " [" << agency.money << "]" << endl;
    int recorredor;
    for(recorredor = 0; recorredor < agency.influencers.size(); recorredor++){
        os << agency.influencers[recorredor];
    }
    return os;
}


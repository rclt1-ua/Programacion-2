#include "SNFollowers.h"
#include "Util.h"
#include "Influencer.h"

Influencer::Influencer(string name){
    this->name = name;
    this->commission = 0.1;
}

void Influencer::setCommission(double commission){
    if(commission > 0 && commission < 0.8){
        this->commission = commission;
    }else{throw EXCEPTION_WRONG_COMMISSION;}
}

void Influencer::addFollowers(string snName,int nFollowers){
    int recorredor;
    for(recorredor = 0; recorredor < followers.size(); recorredor++){
        if(followers[recorredor].getName() == snName){
            followers[recorredor].addFollowers(nFollowers);
            return;
        }
    }
    try{
        SNFollowers snf(snName,nFollowers);
        followers.push_back(snf);
    }catch(exception &e){cout << ERR_UNKNOWN_SN << endl;}
}


void Influencer::addEvent(int nsns,string sn[],double rat[]){// CREO QUE ESTA MAL
    int recorredor;
    for(recorredor = 0; recorredor < nsns; recorredor++){
        int recorredor2;
        for(recorredor2 = 0; recorredor2 < followers.size(); recorredor2++){
            if(followers[recorredor2].getName() == sn[recorredor]){
                followers[recorredor2].addEvent(rat[recorredor]);
            }
        }
    }
}

double Influencer::collectCommission(){
    double comision = 0;
    int recorredor;
    for(recorredor = 0; recorredor < followers.size(); recorredor++){
        comision += followers[recorredor].collectCommission(commission);
    }
    return comision;
}

ostream & operator<<(ostream& os, const Influencer &influencer){
    os << "Influencer: " << influencer.name << " (" << influencer.commission << ")" << endl;
    int recorredor;
    for(recorredor = 0; recorredor < influencer.followers.size(); recorredor++){
        os << influencer.followers[recorredor];
    }
    cout << endl;
    return os;
}


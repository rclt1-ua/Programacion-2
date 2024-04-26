#include <iostream>
#include <string>
#include "SNFollowers.h"
#include "SNData.h"


SNFollowers::SNFollowers(string nameM, int initialFollowers){
    SNData sn;
    if(!sn.checkSN(name)){throw invalid_argument("EXCEPTION_UNKNOWN_SN");}
    if(initialFollowers < 0){throw invalid_argument(to_string(initialFollowers));}
    name = nameM;
    numFollowers = initialFollowers;
    money = 0.0;
}   

void SNFollowers::addFollowers(int nf){
    if(nf < 0){throw invalid_argument(to_string(nf));}
    numFollowers += nf;
    if(numFollowers < 0){numFollowers = 0;}
}

void SNFollowers::addEvent(double rating){
    SNData sn;
    double avgRating = sn.getAvgRating(name);
    double avgMonetizing = sn.getAvgMonetizing(name);
    double relation = rating / avgRating;
    int newFollowers = 0;
    int lostFollowers = 0;

    if(rating < 0){throw invalid_argument(to_string(rating));}

    if(relation > 0.8){
        newFollowers = relation * numFollowers;
        numFollowers += newFollowers;
        money += newFollowers * avgMonetizing;
    }
    else{
        lostFollowers = (0.9 - relation) * numFollowers;
        numFollowers -= lostFollowers;
        if(numFollowers < 0){numFollowers = 0;}
    }
}

double SNFollowers::collectCommission(double commission){
    double comissionMoney;
    if(commission <= 0 || commission >= 1){throw invalid_argument(to_string(commission));}
    comissionMoney = money * commission;
    money = 0.0;
    return comissionMoney;
}

ostream& operator<<(ostream& os, const SNFollowers& snf){
    os << "[" << snf.name << "|" << snf.numFollowers << "|" << snf.money << "])";
    return os;
}

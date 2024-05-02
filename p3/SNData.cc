#include "SNData.h"

vector<SocialNetworkData> SNData::sns;

void SNData::newSocialNetwork(string name, double avgR, double avgM){
    SocialNetworkData sN;
    int recorredor;
    for(recorredor = 0; recorredor < sns.size(); recorredor++){
        if(sns[recorredor].name == name){throw invalid_argument(name);}}

    if(avgR <= 0 || avgR >= 1){throw invalid_argument(to_string(avgR));}
    if(avgM <= 0 || avgM >= 1){throw invalid_argument(to_string(avgM));}   
    sN.name = name;
    sN.averageRating = avgR;
    sN.averageMonetizing = avgM;
    sns.push_back(sN);
}

bool SNData::checkSN(string name){
    int recorredor;
    for(recorredor = 0; recorredor < sns.size(); recorredor++){
        if(sns[recorredor].name == name){return true;}}
    return false;
}

double SNData::getAvgRating(string name){
    int recorredor;
    for(recorredor = 0; recorredor < sns.size(); recorredor++){
        if(sns[recorredor].name == name){return sns[recorredor].averageRating;}}
    return 0.0;
}

double SNData::getAvgMonetizing(string name){
    int recorredor;
    for(recorredor = 0; recorredor < sns.size(); recorredor++){
        if(sns[recorredor].name == name){return sns[recorredor].averageMonetizing;}}
    return 0.0;
}
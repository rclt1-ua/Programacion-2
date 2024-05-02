#define INFLUENCER_H
#include <iostream>
#include <vector>
#include "SNFollowers.h"
#include "Util.h"

using namespace std;

class Influencer{
    friend ostream & operator<<(ostream &os, const Influencer &influencer);
    private:
        vector<SNFollowers> followers;
        string name;
        double commission;
    public:
        Influencer(string name);
        void setCommission(double commission);
        void addFollowers(string snName,int nFollowers);
        void addEvent(int nsns,string sn[],double rat[]);
        double collectCommission();
        string getName() const{return name;}
        vector<SNFollowers> Influencer::getFollowers() const{return followers;}
        double Influencer::getCommission() const{return commission;}
};

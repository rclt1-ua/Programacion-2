#define AGENCY_H
#include <iostream>
#include <vector>
#include "Util.h"
#include "Influencer.h"

using namespace std;

class Agency{
    //AMIGAS
    friend ostream& operator<<(ostream& os, const Agency& agency);
    //ATRIBUTOS Y METODOS
    private:
        string name;
        double money;
        vector<Influencer> influencers;
    public:
        Agency(string name, double initialMoney);
        Influencer* searchInfluencer(string infName);
        void addInfluencer(string infName, double commission);
        void addFollowers(string infName, string snName, int nFollowers);
        void newEvent(vector<string> infNames, int nsns, string snNames[], double evtRatings[]);
        void deleteInfluencer(string infName);
        double collectCommissions();
        string getName() const {return name;}
        double getMoney() const {return money;}
};





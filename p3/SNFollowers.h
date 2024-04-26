#define _SNDATA_H_
#include <iostream>
#include <vector>

using namespace std;

class SNFollowers{
    //AMIGAS
    friend ostream& operator<<(ostream& os, const SNFollowers& snf);
    //ATRIBUTOS Y METODOS
    private:
        string name;
        int numFollowers;
        double money;
    public:
        SNFollowers(string name, int initialFollowers);
        void addFollowers(int nf);
        void addEvent(double rating);
        double collectCommission(double commission);
        string getName() const {return name;}
        int getNumFollowers() const {return numFollowers;}
        double getMoney() const {return money;}
};




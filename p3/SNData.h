#define _SNDATA_H_
#include <iostream>
#include <vector>

using namespace std;

struct SocialNetworkData{
    string name;
    double averageRating;
    double averageMonetizing;
};

class SNData{
    private:
        vector<SocialNetworkData> sns;
    public:
        void newSocialNetwork(string name, double avgR, double avgM);
        bool checkSN(string name);
        double getAvgRating(string name);
        double getAvgMonetizing(string name);
};


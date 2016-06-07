#ifndef GENEVANN_INDIVIDUAL_H
#define GENEVANN_INDIVIDUAL_H

#include <vector>;

using namespace std;

class individual {

public:
    void mutate();
    individual cross(const individual parent);
private:
    vector<double> solution;
};

#endif //GENEVANN_INDIVIDUAL_H

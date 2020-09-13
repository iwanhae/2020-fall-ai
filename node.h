#include <vector>

using namespace std;

class Node {
private:
    vector<double> w;
    double bias;
    double (*activation)(double);
public:
    bool setWeight(vector<double> w);
    bool setActivation(double (*activation)(double));
    bool setBias(double bias);
    double forward(vector<double> input);
    void print();
};
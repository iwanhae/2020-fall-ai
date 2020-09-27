#include <vector>

using namespace std;

class Node {
private:
    vector<double> x;
    vector<double> w;
    double bias;
    double (*activation)(double);
    double (*devOfActivation)(double);
public:
    bool setWeight(vector<double> w);
    bool setActivation(double (*activation)(double));
    bool setDevOfActivation(double (*devOfActivation)(double));
    bool setBias(double bias);
    double forward(vector<double> input);
    vector<double> backward(double error, double c);
    void print();
};
#include <iostream>
#include <vector>
#include <functional>

using namespace std;


class Node {
private:
    vector<double> x;
    vector<double> w;
    vector<double> dw;
    int backward_count = 0;
    double bias;
    double db = 0.0;
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

    function<double (double)> printFunc();
};
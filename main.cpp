#include <iostream>
#include <ctime>
#include "node.h"

using namespace std;
struct aim {
    vector<double> input;
    double output;
};
vector<aim> data = {
    {{0, 0}, 0},
    {{1, 0}, 0},
    {{0, 1}, 0},
    {{1, 1}, 1}
};
double getRandNum() {
    return ((rand() % 200) / 100.0) - 1.0;
}
int main()
{
    srand((unsigned int)time(0));
    Node singleNode;
    auto f = [](double x) -> double { return 0 < x ? 1.0 : 0.0; };

    bool pass = false;
    while (!pass) {
        singleNode.setBias(getRandNum());
        singleNode.setWeight(vector<double>{getRandNum(), getRandNum()});
        singleNode.setActivation(f);
        
        system("clear");
        pass = true;
        for(auto set : data) {          
            double in = singleNode.forward(set.input);
            double out = set.output;
            cout << in << "\t" << out << "\t" << (in == out ? "GOOD" : "WRONG") << endl;            
            if(in != out) pass = false;
        }        
    }
    singleNode.print();
    return 0;
}
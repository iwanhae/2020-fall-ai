#include <vector>
#include "node.h"

using namespace std;

struct layer
{
    vector<double> input;
    vector<Node> nodes;
    vector<double> output;
};

layer InitLayer(int input_n, int node_n, double (*activation)(double), double (*devOfActivation)(double));


class Net {
public:
    Net(vector<layer> layers);
    vector<layer> layers;

    vector<double> forward(vector<double> input);
    void backward(double error, double c);
};
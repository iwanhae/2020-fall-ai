#include <iostream>
#include "node.h"


bool Node::setWeight(vector<double> w) {
    this->w = w;
    return true;
}
bool Node::setBias(double b) {
    this->bias = b;
    return true;
}

bool Node::setActivation(double (*activation)(double)) {
    this->activation = activation;
    return true;
}
bool Node::setDevOfActivation(double (*devOfActivation)(double)) {
    this->devOfActivation = devOfActivation;
    return true;
}

double Node::forward(vector<double> input) {
    this->x = input;
    int len = w.size();
    double output = 0.0;
    for(int i = 0; i<len; i++) {
        output += input.at(i) * w.at(i);
    }
    output-=bias;
    return activation(output);
}

vector<double> Node::backward(double error, double c) {
    vector<double> err;
    double constant = c * error * devOfActivation(error);
    int len = w.size();
    bias -= constant;
    for(int i = 0; i < len; i++){
        err.push_back(constant * w[i]);
        w[i] += constant * x[i];
    }
    return err;
}

void Node::print() {
    int count = 0;
    cout << "bias :\t" << this->bias << endl;
    for(auto w : this->w) cout << "weight " << count++ << ":\t" << w << endl;
    
}
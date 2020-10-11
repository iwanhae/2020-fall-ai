#include <iostream>
#include <functional>
#include "node.h"


bool Node::setWeight(vector<double> w) {
    this->w = w;
    while(w.size() != dw.size()) dw.push_back(0.0);
    return true;
}
bool Node::setBias(double b) {
    this->bias = b;
    this -> db = 0;
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
    output+=bias;
    return activation(output);
}

vector<double> Node::backward(double error, double c) {
    vector<double> err;
    int len = w.size();
    double net = 0;
    for(int i = 0; i < len; i++) net += x[i] * w[i];
    net += bias;
    double constant = c * error * devOfActivation(net);
    bias += constant;
    for(int i = 0; i < len; i++){
        err.push_back(constant * w[i]);
        w[i] += constant * x[i];
    }
    backward_count++;
    return err;
}


void Node::print() {
    int count = 0;
    cout << "bias :\t" << this->bias << endl;
    for(auto w : this->w) cout << "weight " << count++ << ":\t" << w << endl;
}

// 입력이 두개인 상황 한정, 현재 노드상태를 직선으로 출력해준다.
function<double (double)> Node::printFunc() {
    return [&](double x) -> double { return (this->w[0]*x + this->bias)/(-w[1]); };
}
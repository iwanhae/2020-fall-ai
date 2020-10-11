#include "net.h"

using namespace std;

//-1.0 ~ 1.0 사이의 임의의 실수 구하는 함수
double getRandNum() {
    return ((rand() % 200) / 100.0) - 1.0;
}

layer InitLayer(int input_n, int node_n, double (*activation)(double), double (*devOfActivation)(double)){
    layer singleLayer;
    for(int i = 0; i < node_n; i++) {
        Node singleNode;

        //Random 하게 초기화
        singleNode.setBias(getRandNum());
        vector<double> w;
        for(int j = 0; j < input_n; j++) w.push_back(getRandNum());
        singleNode.setWeight(w);
        singleNode.setActivation(activation);
        singleNode.setDevOfActivation(devOfActivation);

        singleLayer.nodes.push_back(singleNode);
    }
    return singleLayer;
}

Net::Net(vector<layer> layers){
    for(auto l : layers) {
        this->layers.push_back(l);
    }
}

vector<double> Net::forward(vector<double> input){
    vector<double> output;
    for(auto& l : layers) {
        output.clear();
        l.input = input;
        for(auto& n : l.nodes) {
            output.push_back(n.forward(l.input));
        }
        l.output = output;
        input = output;
    }
    return output;
}


void Net::backward(double error, double c){
    vector<double> err;
    vector<layer>::reverse_iterator rvLayer;
    rvLayer = layers.rbegin();
    {
        auto& l = *rvLayer;
        for(auto& n : l.nodes) {
            vector<double> tmp = n.backward(error, c);
            while (err.size() != tmp.size())err.push_back(0.0);
            for(int i = 0; i < err.size(); i++) err[i] += tmp[i];
        }
    }
    for (rvLayer++ ; rvLayer != layers.rend( ); rvLayer++) {
        auto& l = *rvLayer;
        vector<double> tmp_err;
        int i = 0;
        for(auto& n : l.nodes) {
            vector<double> tmp = n.backward(err[i++], c);
            while (tmp_err.size() != tmp.size()) tmp_err.push_back(0.0);
            for(int i = 0; i < tmp_err.size(); i++) tmp_err[i] += tmp[i];
        }        
        err = tmp_err;
    }
}

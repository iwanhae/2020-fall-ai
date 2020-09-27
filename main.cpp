#include <iostream>
#include <ctime>
#include <cmath>
#include "node.h"

using namespace std;
struct aim {
    vector<double> input;
    double output;
};

//AND 입력데이터와 출력데이터
vector<aim> data = {
    {{0, 0}, 0},
    {{1, 0}, 1},
    {{0, 1}, 1},
    {{1, 1}, 0}
};

//-1.0 ~ 1.0 사이의 임의의 실수 구하는 함수
double getRandNum() {
    return ((rand() % 200) / 100.0) - 1.0;
}
int main()
{
    srand((unsigned int)time(0));

    //단일 노드
    Node singleNode;
    //아주 단순한 binary Activation 함수
    auto f = [](double x) -> double { return 1 / (1 + std::exp(-x)); };
    auto devf = [](double x) -> double { auto f = [](double x) -> double { return 1 / (1 + std::exp(-x)); }; return f(x)*(1-f(x)); };

    //Random 하게 초기화
    singleNode.setBias(getRandNum());
    singleNode.setWeight(vector<double>{getRandNum(), getRandNum()});
    singleNode.setActivation(f);
    singleNode.setDevOfActivation(devf);

    int iter = 0;
    bool pass = false;
    while (!pass) {        
        iter++;
        double error = 0;
        for(auto set : data) {          
            double in = singleNode.forward(set.input);
            double out = set.output;
            singleNode.backward(out - in, 0.1);
            error += (in - out) * (in - out);
        }
        if(iter == 1000) break;
        if (error < 0.1) break;
        cout << error << endl;
        /*
        // matlab으로 그래프 출력용
        cout << "y = [ y; (";
        singleNode.print();
        cout << " )];" << endl;
        */
    }
    //노드정보 출력
    singleNode.print();
    return 0;
}
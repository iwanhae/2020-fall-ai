#include <iostream>
#include <ctime>
#include "node.h"

using namespace std;
struct aim {
    vector<double> input;
    double output;
};

//AND 입력데이터와 출력데이터
vector<aim> data = {
    {{0, 0}, 0},
    {{1, 0}, 0},
    {{0, 1}, 0},
    {{1, 1}, 1}
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
    auto f = [](double x) -> double { return 0 < x ? 1.0 : 0.0; };
    auto devf = [](double x) -> double { return 1.0; };

    //Random 하게 초기화
    singleNode.setBias(getRandNum());
    singleNode.setWeight(vector<double>{getRandNum(), getRandNum()});
    singleNode.setActivation(f);
    singleNode.setDevOfActivation(devf);

    bool pass = false;
    while (!pass) {        
        system("clear");
        pass = true;
        for(auto set : data) {          
            double in = singleNode.forward(set.input);
            double out = set.output;
            singleNode.backward(out - in, 0.5);
            cout << in << "\t" << out << "\t" << (in == out ? "GOOD" : "WRONG") << endl;
            //하나로도 성공 못한 케이스가 있으면 다시 루프
            if(in != out) pass = false;
        }
    }
    //노드정보 출력
    singleNode.print();
    return 0;
}
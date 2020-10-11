#include <iostream>
#include <fstream>
#include <ctime>
#include <cmath>
#include "net.h"

using namespace std;

struct aim {
    vector<double> input;
    double output;
};

//Donut 입력데이터와 출력데이터
vector<aim> data = {
    {{0, 0}, 0},
    {{1, 0}, 0},
    {{0, 1}, 0},
    {{1, 1}, 0},
    {{0, 0.5}, 0},
    {{0.5, 0}, 0},
    {{1, 0.5}, 0},
    {{0.5, 1}, 0},
    {{0.5, 0.5}, 1},
};

/**
 * json 형태로 좌표 출력 후 python matplotlib에서 시각화 
 */
//plotter 2차원 평면상 주어진 함수를 시각화해주는 함수.
void plotter(char* filename, vector<function<double (double)>> fs);
//plotter 2차원 평면상 주어진 모델을 시각화해주는 함수.
void scatter(char *filename, Net net);

int main()
{
    srand((unsigned int)time(0));
    // 시각화 출력용 임시 변수
    char fname[100];

    // Activation Functions
    auto sigmoid = [](double x) -> double { return 1 / (1 + std::exp(-x)); };
    auto sigmoiddev = [](double x) -> double { auto f = [](double x) -> double { return 1 / (1 + std::exp(-x)); }; return f(x)*(1-f(x)); };
    auto relu = [](double x) -> double { return 0 < x ? x : 0.1 * x; };
    auto reludev = [](double x) -> double { return 0 < x ? 1.0 : 0.1; };


    // 모델 초기화.
    // input : 2
    // hidden: 2
    // output: 1
    Net net({
        InitLayer(2, 2, relu, reludev),
        InitLayer(2, 1, sigmoid, sigmoiddev),    
      }
    );

    int iter = 0;
    while (true) {        
        iter++;
        double error = 0;
        for(auto set : data) {          
            vector<double> pred_output = net.forward(set.input);
            vector<double> output { set.output };

            net.backward( output[0] - pred_output[0], 0.1); // 학습
            error += (output[0] - pred_output[0]) * (output[0] - pred_output[0]) / 2;
        }

        cout << "iter: " << iter << "\terror: " << error << endl;
        
        if (error < 0.001) break; // error 가 0.001 이하면 종료

        /*
        // 시각화 출력 함수
        if(iter % 10000 == 0){
            
            sprintf(fname, "./tmp/%010d.json", iter);            
            plotter(fname, { 
                net.layers[0].nodes[0].printFunc(), 
                net.layers[0].nodes[1].printFunc(),
                net.layers[0].nodes[2].printFunc(),                
                net.layers[0].nodes[3].printFunc(),                
                });                
            sprintf(fname, "./tmp2/%010d.json", iter);
            scatter(fname, net);
        } 
        */
    }
    return 0;
}



void plotter(char* filename, vector<function<double (double)>> fs) {
    ofstream fout;
    fout.open(filename);
    fout << "[";
    {
        fout << "[";
        for(double x = -0.5; x <= 1.5; x += 0.1) fout << x << ",";
        fout.seekp(-1, ios::end);
        fout << "],";
    }
    for(auto f : fs) {
        fout << "[";
        for(double x = -0.5; x <= 1.5; x += 0.1)fout << f(x) << ",";
        fout.seekp(-1, ios::end);
        fout << "],";
    }
    fout.seekp(-1, ios::end);
    fout << "]" << endl;
    fout.close();
}

void scatter(char *filename, Net net) {
    ofstream fout;
    vector<double> xs, ys;
    for(double x = -0.5; x <= 1.5; x += 0.01) {
        for(double y = -0.5; y <= 1.5; y += 0.01) {
            double tmp = net.forward({x, y})[0];
            if(tmp > 0.5) {
                xs.push_back(x);
                ys.push_back(y);
            }
        }
    }
    fout.open(filename);  
    fout << "[";    
    {
        fout << "[";
        for(auto x : xs) fout << x << ",";
        if (xs.size() > 0) fout.seekp(-1, ios::end);
        fout << "],";
    }
    {
        fout << "[";
        for(auto y : ys) fout << y << ",";
        if (ys.size() > 0) fout.seekp(-1, ios::end);
        fout << "]";
    }
    fout << "]" << endl;
    fout.close();
}
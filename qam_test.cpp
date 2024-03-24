#include <iostream>
#include <vector>
#include "QamMod.cpp"
#include "GausNoise.cpp"
#include "Demodulator.cpp"

using namespace std;

int main(){
    system("color f0");
    vector<string> strvec;
    strvec.push_back("1111");
    strvec.push_back("1110");
    strvec.push_back("1101");
    strvec.push_back("1100");
    strvec.push_back("1011");
    strvec.push_back("1010");
    strvec.push_back("1001");
    strvec.push_back("1000");
    strvec.push_back("0111");
    strvec.push_back("0110");
    strvec.push_back("0101");
    strvec.push_back("0100");
    strvec.push_back("0011");
    strvec.push_back("0010");
    strvec.push_back("0001");
    strvec.push_back("0000");
    QamMod qammas(strvec);
    double i_sr;
    double q_sr;
    GausNoise mom(qammas.modulated);
    Demodulator dem(qammas.modulated, qammas.fc, qammas.ts, strvec.size());
    cout << '\n';
    for(int i = 0; i < dem.demodulated.size(); i+= dem.demodulated.size()/strvec.size()){
        cout << dem.demodulated[i] << ' ';
    }
    cout << '\n';
    for(int i = 0; i < dem.str_res.size(); i++){
        cout << dem.str_res[i] << ' ';
    }
    int summ = 0;
    for(int i = 0; i < strvec.size(); i++){
        for(int j = 0; j < strvec[i].length(); j++){
            if(strvec[i][j]!=dem.str_res[i][j]) summ++;
        }
    }
    cout << '\n';
    cout << summ;
    cout << '\n';
}
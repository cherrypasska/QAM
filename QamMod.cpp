#include <vector>
#include <complex>
#include <string>
#include <iostream>

using namespace std;

const double pi = 3.14159265358979323846;

template <typename T>
vector<complex<T>> repelem(const vector<complex<T>>& input, int repetitions){
    vector<complex<T>> output;
    for (const complex<T> elem : input){
        for (int i = 0; i < repetitions; ++i){
            output.push_back(elem);
        }
    }
    return output;
}

class QamMod{
private:
    int fs = 10000;
    int N = 20000;
    int M;
    double I;
    double Q;
    double real;
    double imag;
    double qamEl;
public:
    vector<double> modulated;
    vector<complex<double>> data;
    vector<double> ts;
    const int fc = 1000; //несущая частота
    QamMod(vector<string> digitalData){
        int Nd = digitalData.size();

        int bit_size = N/Nd;
        double t = 0;
        for(int i = 0; i < N; i++){
            ts.push_back(t);
            t += 1.0/fs;
        }
        for(int i = 0; i < digitalData.size(); i++){
            modulate(digitalData[i]);
            complex<double> X(I, Q);
            data.push_back(X);
        }
        vector<complex<double>> qdata = repelem(data,bit_size);
        for(int i = 0; i < N; i++){
            real = qdata[i].real() * cos(2 * pi * ts[i] * fc);
            imag = qdata[i].imag() * sin(2 * pi * ts[i] * fc);
            qamEl = real + imag;
            modulated.push_back(qamEl);
        }
    }
    void modulate(string digital_i){
        I = 1;
        Q = 1;
        if(digital_i.length()%2 == 1){
            cout << "the length of the string must be a multiple of 2";
            return;
        }
        if(digital_i.length() == 2){
            if(digital_i[0] == '0') I *= -1;
            if(digital_i[1] == '0') Q *= -1;
        }
        else if(digital_i.length() == 4){
            if(digital_i[0] == '0') I *= -1;
            if(digital_i[2] == '0') Q *= -1;
            if(digital_i[1] == '1') I *= 3;
            if(digital_i[3] == '1') Q *= 3;
        }
        else if(digital_i.length() < 7){
            I = 1;
            Q = 1;
            if(digital_i[0] == '0'){
                I = I * -1;
            }
            if(digital_i[3] == '0'){
                Q = Q * -1;
            }
            if(digital_i[1]=='0' && digital_i[2] == '0') I = I*7;
            else if(digital_i[1] == '0' && digital_i[2] == '1') I = I*5;
            else if(digital_i[1] == '1' && digital_i[2] == '1') I = I*3;
            if(digital_i[4]=='0' && digital_i[5] == '0') Q = Q*7;
            else if(digital_i[4] == '0' && digital_i[5] == '1') Q = Q*5;
            else if(digital_i[4] == '1' && digital_i[5] == '1') Q = Q*3;
        }
    }
};
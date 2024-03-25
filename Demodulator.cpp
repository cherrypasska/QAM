#include <vector>
#include <complex>

using namespace std;

const double pi_ = 3.14159265358979323846;

class Demodulator{
private:
    double real;
    double imag;
    double real_cnt;
    double imag_cnt;
    int cnt = 0;
    double max = -8.0;
    double min = 8.0;
public:
    vector<complex<double>> demodulated;
    vector<double> real_mass;
    vector<double> imag_mass;
    vector<string> str_res;
    Demodulator(vector<double> modulated, int fs, vector<double> ts, int k){
        for(int i = 0; i < modulated.size()-(modulated.size()%k); i++){
            real = 2 * modulated[i] * cos(2 * pi_ * ts[i] * fs);
            real_cnt += real;
            imag = 2 * modulated[i] * sin(2 * pi_ * fs * ts[i]);
            imag_cnt += imag;
            cnt++;
            if(cnt%5 == 0){
                complex<double> S_t(round(real_cnt/5),round(imag_cnt/5));
                for(int j = 0; j < 5; j++){
                    demodulated.push_back(S_t);
                }
                imag_cnt = 0.0;
                real_cnt = 0.0;
            }
        }
        for(int i = 0; i < demodulated.size()-(modulated.size()%k); i += modulated.size()/k+1){
            if(demodulated[i].imag() > max) max = demodulated[i].imag();
            if(demodulated[i].real() > max) max = demodulated[i].real();
            if(demodulated[i].imag() < min) min = demodulated[i].imag();
            if(demodulated[i].real() < min) min = demodulated[i].real();
        }
        if(min >= -1.5 && max <= 1.5){
            for(int i = 0; i < demodulated.size()-(modulated.size()%k); i+= modulated.size()/k+1){
                if(demodulated[i].real() == 1.0){
                    if(demodulated[i].imag() == 1.0){
                        str_res.push_back("11");
                    }
                    else str_res.push_back("10");
                }
                else{
                    if(demodulated[i].imag() == 1){
                        str_res.push_back("01");
                    }
                    else str_res.push_back("00");
                }
            }
        }
        string st;
        string st_im;
        if(min >= -4.0 && max <= 4.0){
            for(int i = 0; i < demodulated.size()-(modulated.size()%k); i+= modulated.size()/k+1){
                st = func_16(demodulated[i].real());
                st_im = func_16(demodulated[i].imag());
                str_res.push_back(st+st_im);
            }
        }
        else{
            for(int i = 0; i < demodulated.size()-(modulated.size()%k); i+= modulated.size()/k+1){
                st = func_64(demodulated[i].real());
                st_im = func_64(demodulated[i].imag());
                str_res.push_back(st+st_im);
            }
        }
    }
    string func_16(double mom){
        string h;
        if(mom > 0.0){
            h += "1";
            if(mom > 1.0){
                h += "1";
            }
            else h += "0";
        }
        else{
            h += "0";
            if(mom <= -2.0){
                h += "1";
            }
            else{
                h += "0";
            }
        }
        return h;
    }
    string func_64(double mom){
        string h;
        if(mom > 0.0){
            h += "1";
            if(mom > 3.0){
                h += "0";
                if(mom > 5.0) h+="0";
                else h+="1";
            }
            else{
                h += "1";
                if(mom > 2.0) h += "1";
                else h += "0";
            }
        }
        else{
            h += "0";
            if(mom < -3.0){
                h += "1";
                if(mom < -5.0) h += "1";
                else h += "0";
            }
            else{
                h += "0";
                if(mom < -2.0) h += "1";
                else h += "0";
            }
        }
        return h;
    }
};

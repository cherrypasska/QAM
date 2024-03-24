#include <random>
#include <vector>

using namespace std;

class GausNoise{
private:
    const double min = 0.0;
    const double max = 0.1;
    default_random_engine gausGenerator;
public:
    GausNoise(vector<double> &data){
        normal_distribution<double> noise(min,max);
        for(int i = 0; i < data.size(); i++){
            data[i] += noise(gausGenerator);
        }
    }
};
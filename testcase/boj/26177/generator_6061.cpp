#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for diversity
    const int Hmax = 10;
    const int Wmax = 10;
    vector<int> wparams = {-1, 0, 1};
    int th = rnd.any(wparams);
    int tw = rnd.any(wparams);
    int h = rnd.wnext(Hmax, th) + 1;
    int w = rnd.wnext(Wmax, tw) + 1;

    // Probability of towers
    vector<double> prob = {0.0, 0.2, 0.5, 0.8, 1.0};
    double p = rnd.any(prob);

    // Output the grid
    println(h, w);
    for (int i = 0; i < h; i++) {
        string row;
        for (int j = 0; j < w; j++) {
            row += (rnd.next() < p ? 'O' : 'X');
        }
        println(row);
    }
    return 0;
}

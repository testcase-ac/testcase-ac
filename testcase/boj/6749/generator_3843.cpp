#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for weighted sampling
    vector<int> t_list = { -2, -1, 0, 1, 2 };
    // Sample youngest age Y in [0,50], skewed by tY
    int tY = rnd.any(t_list);
    int Y = rnd.wnext(51, tY);
    // Sample difference delta = M-Y in [0,50-Y], skewed by tDelta
    int deltaMax = 50 - Y;
    int tDelta = rnd.any(t_list);
    int delta = rnd.wnext(deltaMax + 1, tDelta);
    int M = Y + delta;

    // Output two lines: Y then M
    println(Y);
    println(M);

    return 0;
}

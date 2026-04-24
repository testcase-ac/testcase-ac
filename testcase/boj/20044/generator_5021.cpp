#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // number of teams
    int n = rnd.next(1, 10);
    int total = 2 * n;
    // maximum possible weight
    int Wmax = rnd.next(total, 100);
    // choose generation mode
    int mode = rnd.next(0, 1);
    vector<int> w;
    if (mode == 0 && Wmax >= 4 * n) {
        // cluster: n small, n large
        int lowMax = Wmax / 4;
        int highMin = 3 * Wmax / 4 + 1;
        // build ranges
        vector<int> lowVals, highVals;
        for (int x = 1; x <= lowMax; ++x) lowVals.push_back(x);
        for (int x = highMin; x <= Wmax; ++x) highVals.push_back(x);
        shuffle(lowVals.begin(), lowVals.end());
        shuffle(highVals.begin(), highVals.end());
        for (int i = 0; i < n; ++i) w.push_back(lowVals[i]);
        for (int i = 0; i < n; ++i) w.push_back(highVals[i]);
    } else {
        // uniform distinct sample from 1..Wmax
        vector<int> pool;
        for (int x = 1; x <= Wmax; ++x) pool.push_back(x);
        shuffle(pool.begin(), pool.end());
        for (int i = 0; i < total; ++i) w.push_back(pool[i]);
    }
    // final shuffle of output order
    shuffle(w.begin(), w.end());

    // output
    println(n);
    println(w);
    return 0;
}

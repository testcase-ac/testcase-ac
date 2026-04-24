#include "testlib.h"
#include <vector>
#include <string>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // number of test cases, weighted to get small or large T
    int tparam = rnd.next(-1, 1);
    int T = rnd.wnext(10, tparam);
    if (T < 1) T = 1;
    println(T);

    // A few hand-picked tricky prices for rounding checks
    vector<string> specials = {
        "0.01", "0.06", "0.07", "0.12",
        "20.00", "59.99", "100.00", "1.25", "1000.00"
    };
    // possible max integer parts
    vector<int> limits = {0, 9, 99, 999};

    double specialProb = 0.3;
    for (int i = 0; i < T; i++) {
        if (!specials.empty() && rnd.next() < specialProb) {
            int idx = rnd.next((int)specials.size() - 1);
            string s = specials[idx];
            specials.erase(specials.begin() + idx);
            println(s);
        } else {
            int maxInt = rnd.any(limits);
            int ip = rnd.next(0, maxInt);
            int cents = rnd.next(0, 99);
            printf("%d.%02d\n", ip, cents);
        }
    }
    return 0;
}

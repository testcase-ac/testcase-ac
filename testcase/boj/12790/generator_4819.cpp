#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of test cases, biased towards larger small values
    int T = rnd.wnext(10, 2) + 1;  // from 1 to 10, skewed high
    println(T);
    for (int i = 0; i < T; i++) {
        vector<int> base(4), delta(4);
        // Generate base stats: HP, MP, Atk, Def
        for (int j = 0; j < 4; j++) {
            double r = rnd.next();
            if (r < 0.05) {
                base[j] = 1;        // extreme low
            } else if (r < 0.10) {
                base[j] = 999;      // extreme high
            } else {
                base[j] = rnd.next(1, 999);
            }
        }
        // Generate equipment deltas
        for (int j = 0; j < 4; j++) {
            double r = rnd.next();
            if (r < 0.05) {
                delta[j] = -999;    // extreme negative
            } else if (r < 0.10) {
                delta[j] = 999;     // extreme positive
            } else if (r < 0.20) {
                delta[j] = 0;       // no change
            } else {
                delta[j] = rnd.next(-500, 500);  // moderate change
            }
        }
        // Merge and output one test case
        vector<int> stats;
        stats.reserve(8);
        for (int x : base) stats.push_back(x);
        for (int x : delta) stats.push_back(x);
        println(stats);
    }
    return 0;
}

#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // True density per m^2 and area
    int L = rnd.next(1, 10);
    int P = rnd.next(1, 1000);
    int correct = L * P;

    // Generate five reported values with diverse error patterns
    vector<int> reported(5);
    for (int i = 0; i < 5; i++) {
        int mode = rnd.next(0, 9);
        if (mode == 9) {
            // Occasional completely random outlier
            reported[i] = rnd.next(1, 999999);
        } else {
            int err;
            if (mode < 4) {
                // small error
                err = rnd.next(-5, 5);
            } else if (mode < 7) {
                // medium error
                err = rnd.next(-100, 100);
            } else {
                // large error
                err = rnd.next(-1000, 1000);
            }
            int x = correct + err;
            // clip into valid range [1, 10^6-1]
            if (x < 1) x = 1;
            if (x > 999999) x = 999999;
            reported[i] = x;
        }
    }

    // Output
    println(L, P);
    println(reported);

    return 0;
}

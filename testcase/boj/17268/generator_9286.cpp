#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int N;
    // 50%: random even with various distributions
    if (rnd.next(0, 1) == 0) {
        int mode = rnd.next(0, 2);
        int k; // we'll generate k in [0..4999], then N = 2*(k+1) in [2..10000]
        if (mode == 0) {
            // Uniform over all valid even N
            k = rnd.next(0, 4999);
        } else if (mode == 1) {
            // Bias towards larger N
            k = rnd.wnext(5000, +3);
        } else {
            // Bias towards smaller N
            k = rnd.wnext(5000, -3);
        }
        N = 2 * (k + 1);
    } else {
        // 50%: choose from a curated set of interesting even values
        vector<int> special = {
            2, 4, 6, 8, 10,
            12, 14, 16, 18, 20,
            22, 24, 26, 28, 30, 32,
            36, 40, 50, 60, 100, 200,
            202, 500, 998, 1000,
            1500, 1998, 2000, 2048,
            3000, 4096, 5000, 8000,
            8192, 9000, 9900, 9998, 10000
        };
        N = rnd.any(special);
    }

    println(N);
    return 0;
}

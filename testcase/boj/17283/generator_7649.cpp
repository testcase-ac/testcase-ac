#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int L, R;
    long long sum;
    // Generate until sum of branches <= 1e6
    do {
        // Hyper-parameter for L: sometimes bias to large, sometimes uniform
        if (rnd.next(2) == 0) {
            // bias towards large L
            L = rnd.wnext(10000 - 6 + 1, 3) + 6;  // [6,10000], max of 4 samples
        } else {
            L = rnd.next(6, 10000);
        }
        // Hyper-parameter for R: sometimes bias to small, sometimes uniform
        if (rnd.next(2) == 0) {
            // bias towards small R
            R = rnd.wnext(99, -2) + 1; // [1,99], min of 3 samples
        } else {
            R = rnd.next(1, 99);
        }
        // compute total branch length
        sum = 0;
        int len = L * R / 100;
        long long cnt = 2;
        while (len > 5) {
            if (cnt > 1000000) { sum = 1000001; break; }
            sum += cnt * len;
            len = len * R / 100;
            cnt <<= 1;
        }
    } while (sum > 1000000);

    // Output one test case
    println(L);
    println(R);
    return 0;
}

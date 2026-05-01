#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter for N: sometimes small, mid, or larger
    int r = rnd.next(99);
    int N;
    if (r < 20) {
        N = rnd.next(1, 5);
    } else if (r < 80) {
        N = rnd.next(6, 15);
    } else {
        N = rnd.next(16, 30);
    }
    // Decide if there's at least one valid student
    bool hasValid = rnd.next(99) < 80;  // 80% chance to have valid
    vector<bool> isValid(N, false);
    if (hasValid) {
        int maxv = min(N, 3);
        int vCount = rnd.next(1, maxv);
        vector<int> idx(N);
        iota(idx.begin(), idx.end(), 0);
        shuffle(idx.begin(), idx.end());
        for (int i = 0; i < vCount; i++)
            isValid[idx[i]] = true;
    }
    println(N);
    for (int i = 0; i < N; i++) {
        int s;
        if (isValid[i]) {
            // sum at least 512, up to ~600, skew a bit upward
            s = 512 + rnd.wnext(89, 2);  // gives 512..600
        } else {
            // sum strictly below 512
            s = rnd.next(0, 511);
        }
        // build a+b+c = s with each in [0,200]
        int c_lo = max(0, s - 400);
        int c_hi = min(200, s);
        int c = rnd.next(c_lo, c_hi);
        int rem = s - c;
        int a_lo = max(0, rem - 200);
        int a_hi = min(200, rem);
        int a = rnd.next(a_lo, a_hi);
        int b = rem - a;
        println(a, b, c);
    }
    return 0;
}

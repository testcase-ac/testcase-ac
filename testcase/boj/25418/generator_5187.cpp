#include "testlib.h"
#include <vector>
#include <cmath>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int maxVal = 1000000;
    vector<int> biases = {-3, -1, 0, 1, 3};
    int type = rnd.next(0, 3);
    int A, K;
    if (type == 0) {
        // small additive gap
        A = rnd.next(1, maxVal / 2);
        int d = rnd.next(1, 20);
        K = A + d;
    } else if (type == 1) {
        // power-of-two multiplication
        A = rnd.next(1, maxVal - 1);
        int maxp = (int)floor(log2((double)maxVal / A));
        if (maxp < 1) maxp = 1;
        int p = rnd.next(1, maxp);
        long long tmp = (long long)A << p;
        if (tmp > maxVal) tmp = maxVal;
        K = (int)tmp;
        if (K <= A) {
            K = min(A + 1, maxVal);
        }
    } else if (type == 2) {
        // small A, moderate multiplier then random in range
        A = rnd.next(1, 100);
        int mul = rnd.next(2, 5);
        long long tmp = (long long)A * mul;
        if (tmp > maxVal) tmp = maxVal;
        K = rnd.next(A + 1, (int)tmp);
    } else {
        // full-range with bias extremes
        int tA = rnd.any(biases);
        A = rnd.wnext(maxVal - 1, tA) + 1;
        K = rnd.next(A + 1, maxVal);
    }
    println(A, K);
    return 0;
}

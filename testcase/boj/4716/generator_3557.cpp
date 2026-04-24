#include "testlib.h"
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(1, 5);
    for (int tc = 0; tc < T; tc++) {
        int N = rnd.next(1, 10);
        int Kmax = rnd.next(1, 20);
        vector<int> K(N);
        for (int i = 0; i < N; i++) {
            K[i] = rnd.next(1, Kmax);
        }
        int sumK = accumulate(K.begin(), K.end(), 0);
        int extra = rnd.next(0, sumK);
        int total = sumK + extra;
        int A = rnd.next(0, total);
        int B = total - A;
        println(N, A, B);

        int maxD = rnd.next(0, 20);
        for (int i = 0; i < N; i++) {
            int type = rnd.next(0, 2);
            int dA, dB;
            if (type == 0) {
                dA = rnd.next(0, min(5, maxD));
                if (dA + 1 <= maxD) dB = rnd.next(dA + 1, maxD);
                else dB = rnd.next(0, maxD);
            } else if (type == 1) {
                dB = rnd.next(0, min(5, maxD));
                if (dB + 1 <= maxD) dA = rnd.next(dB + 1, maxD);
                else dA = rnd.next(0, maxD);
            } else {
                dA = rnd.next(0, maxD);
                dB = rnd.next(0, maxD);
            }
            println(K[i], dA, dB);
        }
    }
    println(0, 0, 0);
    return 0;
}

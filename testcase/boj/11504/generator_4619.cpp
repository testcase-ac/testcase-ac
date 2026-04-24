#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // number of test cases
    int T = rnd.next(1, 5);
    println(T);
    // precompute powers of 10 up to 10^9
    vector<int> p10(10, 1);
    for (int i = 1; i < 10; i++) {
        p10[i] = p10[i - 1] * 10;
    }
    for (int tc = 0; tc < T; tc++) {
        // pick N and M
        int N = rnd.next(1, 10);
        int M = rnd.next(1, min(N, 9));
        println(N, M);
        // maximum value for M-digit numbers
        int maxv = p10[M];
        // three types of ranges for diversity
        int type = rnd.next(0, 2);
        int Xv, Yv;
        if (type == 0) {
            // X = 0...0, Y random
            Xv = 0;
            Yv = rnd.next(0, maxv - 1);
        } else if (type == 1) {
            // X random, Y = 9...9
            Xv = rnd.next(0, maxv - 1);
            Yv = maxv - 1;
        } else {
            // both random
            Xv = rnd.next(0, maxv - 1);
            Yv = rnd.next(0, maxv - 1);
        }
        if (Xv > Yv) swap(Xv, Yv);
        // convert Xv, Yv into digit vectors of length M
        vector<int> X(M), Y(M);
        for (int i = 0; i < M; i++) {
            int pw = p10[M - 1 - i];
            X[i] = (Xv / pw) % 10;
            Y[i] = (Yv / pw) % 10;
        }
        println(X);
        println(Y);
        // generate the wheel state
        vector<int> state(N);
        for (int i = 0; i < N; i++) {
            state[i] = rnd.next(0, 9);
        }
        println(state);
    }
    return 0;
}

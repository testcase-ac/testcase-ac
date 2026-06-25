#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int N = rnd.next(1, 24);
    int Q = rnd.next(1, 24);
    int K;
    vector<int> A(N);

    if (mode == 0) {
        K = rnd.next(1, min(N, 5));
        for (int i = 0; i < N; ++i) A[i] = rnd.next(1, min(N, 4));
    } else if (mode == 1) {
        K = rnd.next(2, min(N + 1, 8));
        int value = rnd.next(1, N);
        for (int i = 0; i < N; ++i) A[i] = value;
    } else if (mode == 2) {
        K = rnd.next(2, min(N + 1, 6));
        int period = rnd.next(1, min(N, 5));
        vector<int> base(period);
        for (int i = 0; i < period; ++i) base[i] = rnd.next(1, N);
        for (int i = 0; i < N; ++i) A[i] = base[i % period];
    } else if (mode == 3) {
        K = rnd.next(1, min(N, 6));
        for (int i = 0; i < N; ++i) A[i] = i + 1;
        shuffle(A.begin(), A.end());
    } else if (mode == 4) {
        K = rnd.next(N + 1, min(200000, N + 20));
        for (int i = 0; i < N; ++i) A[i] = rnd.next(1, N);
    } else {
        K = rnd.next(2, min(N + 1, 7));
        int heavy = rnd.next(1, N);
        int blockLen = rnd.next(1, N);
        int start = rnd.next(0, N - blockLen);
        for (int i = 0; i < N; ++i) A[i] = rnd.next(1, N);
        for (int i = start; i < start + blockLen; ++i) {
            if (rnd.next(0, 2) != 0) A[i] = heavy;
        }
    }

    println(N, K, Q);
    println(A);

    for (int i = 0; i < Q; ++i) {
        int l, r;
        int queryMode = rnd.next(0, 4);
        if (queryMode == 0) {
            l = 1;
            r = N;
        } else if (queryMode == 1) {
            l = rnd.next(1, N);
            r = l;
        } else if (queryMode == 2) {
            int len = rnd.next(1, min(N, 5));
            l = rnd.next(1, N - len + 1);
            r = l + len - 1;
        } else {
            l = rnd.next(1, N);
            r = rnd.next(l, N);
        }
        println(l, r);
    }

    return 0;
}

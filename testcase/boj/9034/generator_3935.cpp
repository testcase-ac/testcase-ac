#include "testlib.h"
#include <cstdio>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int T = rnd.next(1, 5);
    println(T);
    for (int tc = 0; tc < T; ++tc) {
        int N = rnd.next(1, 10);
        int maxK = rnd.next(1, 500);
        double qProb = rnd.next(0.0, 1.0);
        int M = rnd.next(1, min(20, N * 5));
        println(N);
        println(M);
        int numQ = 0;
        for (int i = 0; i < M; ++i) {
            bool isQ;
            if (i == M - 1 && numQ == 0) {
                isQ = true;
            } else {
                isQ = rnd.next() < qProb;
            }
            if (isQ) {
                int j = rnd.next(1, N);
                printf("Q %d\n", j);
                numQ++;
            } else {
                int j = rnd.next(1, N);
                int k = rnd.next(1, maxK);
                printf("R %d %d\n", j, k);
            }
        }
    }
    return 0;
}

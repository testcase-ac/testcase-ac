#include "testlib.h"
#include <vector>
#include <cstdio>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters
    int N = rnd.next(2, 10);
    int maxC = rnd.next(0, 20);
    int maxP = rnd.next(0, 20);
    int patternC = rnd.next(0, 2);
    int patternP = rnd.next(0, 2);

    // Prepare matrices
    vector<vector<long long>> C(N, vector<long long>(N));
    vector<vector<long long>> P(N, vector<long long>(N));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            // Corners must be zero
            if ((i == 0 && j == 0) || (i == N-1 && j == N-1)) {
                C[i][j] = 0;
                P[i][j] = 0;
                continue;
            }
            // Fill C based on patternC
            switch (patternC) {
                case 0:
                    C[i][j] = rnd.next(0, maxC);
                    break;
                case 1:
                    C[i][j] = (i == j ? rnd.next(0, maxC) : rnd.next(0, maxC/2));
                    break;
                case 2:
                    C[i][j] = (i==0 || j==0 || i==N-1 || j==N-1 ? rnd.next(0, maxC) : rnd.next(0, maxC/2));
                    break;
            }
            // Fill P based on patternP
            switch (patternP) {
                case 0:
                    P[i][j] = rnd.next(0, maxP);
                    break;
                case 1:
                    P[i][j] = (i == j ? rnd.next(0, maxP) : rnd.next(0, maxP/2));
                    break;
                case 2:
                    P[i][j] = (i==0 || j==0 || i==N-1 || j==N-1 ? rnd.next(0, maxP) : rnd.next(0, maxP/2));
                    break;
            }
        }
    }

    // Output
    println(N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%lld%c", C[i][j], j+1 < N ? ' ' : '\n');
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%lld%c", P[i][j], j+1 < N ? ' ' : '\n');
        }
    }
    return 0;
}

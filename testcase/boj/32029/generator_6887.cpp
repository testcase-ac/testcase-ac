#include "testlib.h"
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of tasks
    int N = rnd.next(1, 12);
    // Initial time per task and sleep factor
    int A = rnd.next(1, 20);
    int B = rnd.next(1, 20);

    vector<int> T(N);
    int mode = rnd.next(0, 2);
    if (mode == 0) {
        // Uniform random deadlines
        for (int i = 0; i < N; i++) {
            T[i] = rnd.next(1, 1000);
        }
    } else if (mode == 1) {
        // Clustered deadlines
        int C = rnd.next(1, min(N, 4));
        vector<int> bases(C);
        for (int j = 0; j < C; j++) {
            bases[j] = rnd.next(1, 1000);
        }
        int maxDelta = (A * N) / 2;
        for (int i = 0; i < N; i++) {
            int b = bases[rnd.next(0, C - 1)];
            int d = rnd.next(-maxDelta, maxDelta);
            T[i] = max(1, b + d);
        }
    } else {
        // Arithmetic progression plus noise
        int start = rnd.next(1, 50);
        int d = rnd.next(0, 50);
        for (int i = 0; i < N; i++) {
            T[i] = start + d * i + rnd.next(0, A);
        }
    }

    // Introduce some duplicate deadlines
    int dupCount = rnd.next(0, N / 3);
    for (int k = 0; k < dupCount; k++) {
        int i = rnd.next(0, N - 1);
        int j = rnd.next(0, N - 1);
        T[j] = T[i];
    }

    // Shuffle to unsort deadlines
    shuffle(T.begin(), T.end());

    // Output
    println(N, A, B);
    println(T);

    return 0;
}

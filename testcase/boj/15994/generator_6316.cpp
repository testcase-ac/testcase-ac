#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of floors N and number of elevators M
    int N = rnd.next(5, 100);
    int M = rnd.next(1, min(7, N));
    vector<int> X(M), Y(M);

    // Generate elevator parameters
    for (int i = 0; i < M; i++) {
        X[i] = rnd.next(1, N);
        if (rnd.next() < 0.1) {
            // 10% chance of Yi = N (only one stop)
            Y[i] = N;
        } else {
            // Yi biased to be small (min of two samples)
            Y[i] = rnd.wnext(N - 1, -1) + 1;
        }
    }

    // Decide A and B
    int A, B;
    if (rnd.next() < 0.2) {
        // 20% chance to ensure simple reachable by single elevator
        int ei = rnd.next(0, M - 1);
        int xi = X[ei], yi = Y[ei];
        // collect stops of elevator ei
        vector<int> stops;
        for (int f = xi; f <= N; f += yi) stops.push_back(f);
        if ((int)stops.size() >= 2) {
            // pick any two distinct stops
            A = rnd.any(stops);
            do { B = rnd.any(stops); } while (B == A);
        } else {
            // fallback to random if not enough stops
            A = rnd.next(1, N);
            do { B = rnd.next(1, N); } while (B == A);
        }
    } else {
        // random A, B (may be unreachable)
        A = rnd.next(1, N);
        do { B = rnd.next(1, N); } while (B == A);
    }

    // Output the test case
    println(N, M);
    for (int i = 0; i < M; i++) {
        println(X[i], Y[i]);
    }
    println(A, B);
    return 0;
}

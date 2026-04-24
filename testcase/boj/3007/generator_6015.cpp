#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Choose N with small to medium sizes for readability
    int modeN = rnd.next(0, 1);
    int N = (modeN == 0 ? rnd.next(3, 10) : rnd.next(11, 30));
    
    // Prepare original circle A
    vector<long long> A(N);
    // Special patterns for variability
    if (rnd.next(0, 9) == 0) {
        // all ones
        for (int i = 0; i < N; i++) A[i] = 1;
    } else if (rnd.next(0, 9) == 0) {
        // small repeating pattern
        int K = rnd.next(1, min(5, N));
        for (int i = 0; i < N; i++) A[i] = (i % K) + 1;
    } else if (rnd.next(0, 9) == 0) {
        // increasing or decreasing sequence
        if (rnd.next(0, 1) == 0) {
            for (int i = 0; i < N; i++) A[i] = i + 1;
        } else {
            for (int i = 0; i < N; i++) A[i] = N - i;
        }
    } else {
        // random values with varied upper bounds
        vector<long long> possibleM = {5, 100, 1000, 100000000};
        long long M = rnd.any(possibleM);
        for (int i = 0; i < N; i++) {
            A[i] = rnd.next(1LL, M);
        }
    }
    
    // Compute the second circle B: each is sum of itself and neighbors
    vector<long long> B(N);
    for (int i = 0; i < N; i++) {
        int l = (i - 1 + N) % N;
        int r = (i + 1) % N;
        B[i] = A[l] + A[i] + A[r];
    }
    
    // Output
    println(N);
    for (int i = 0; i < N; i++) {
        println(B[i]);
    }
    return 0;
}

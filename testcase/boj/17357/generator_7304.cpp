#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose N with a mix of small, medium, and larger sizes (but ≤ 50 for readability)
    double p = rnd.next();
    int N;
    if (p < 0.1) {
        N = rnd.next(1, 3);
    } else if (p < 0.4) {
        N = rnd.next(4, 10);
    } else if (p < 0.8) {
        N = rnd.next(11, 30);
    } else {
        N = rnd.next(31, 50);
    }

    // Choose whether values are small or up to 1e6
    int valMax = (rnd.next() < 0.5 ? 1000 : 1000000);

    // Choose a pattern for the sequence
    vector<string> patterns = {"random", "inc", "dec", "zigzag", "constant"};
    string pat = rnd.any(patterns);

    vector<int> A(N);

    if (pat == "random") {
        // Fully random values
        for (int i = 0; i < N; i++) {
            A[i] = rnd.next(1, valMax);
        }
    }
    else if (pat == "inc") {
        // Strictly (or weakly) increasing
        int maxStep = (N > 1 ? (valMax - 1) / (N - 1) : 0);
        int step = (maxStep >= 1 ? rnd.next(1, maxStep) : 0);
        int start = rnd.next(1, valMax);
        for (int i = 0; i < N; i++) {
            long long v = 1LL * start + 1LL * i * step;
            A[i] = int(min<long long>(v, valMax));
        }
    }
    else if (pat == "dec") {
        // Strictly (or weakly) decreasing
        int maxStep = (N > 1 ? (valMax - 1) / (N - 1) : 0);
        int step = (maxStep >= 1 ? rnd.next(1, maxStep) : 0);
        int start = rnd.next(1, valMax);
        vector<int> tmp(N);
        for (int i = 0; i < N; i++) {
            long long v = 1LL * start + 1LL * i * step;
            tmp[i] = int(min<long long>(v, valMax));
        }
        for (int i = 0; i < N; i++) {
            A[i] = tmp[N - 1 - i];
        }
    }
    else if (pat == "zigzag") {
        // Alternating high and low
        int low = rnd.next(1, valMax / 2);
        int high = rnd.next(valMax / 2 + 1, valMax);
        for (int i = 0; i < N; i++) {
            A[i] = (i % 2 == 0 ? high : low);
        }
    }
    else if (pat == "constant") {
        // Mostly constant with a few random spikes
        int baseVal = rnd.next(1, valMax);
        for (int i = 0; i < N; i++) {
            A[i] = baseVal;
        }
        int k = rnd.next(0, min(3, N));
        for (int j = 0; j < k; j++) {
            int idx = rnd.next(0, N - 1);
            A[idx] = rnd.next(1, valMax);
        }
    }

    // Output the test case
    println(N);
    println(A);

    return 0;
}

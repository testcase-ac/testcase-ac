#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for sizes
    int N = rnd.next(1, 10);
    int M = rnd.next(1, 20);

    // Choose a global maximum bound with bias
    int t_bias = rnd.next(-2, 2);
    int maxBound = rnd.wnext(1000000001, t_bias); // in [0,1e9]

    // Generate non-decreasing upper bounds
    vector<int> ub(N);
    ub[0] = rnd.next(0, maxBound);
    for (int i = 1; i < N; i++) {
        ub[i] = rnd.next(ub[i-1], maxBound);
    }

    // Generate random title names (uppercase, length 1..11)
    vector<string> names(N);
    for (int i = 0; i < N; i++) {
        int len = rnd.next(1, 11);
        string s;
        s.reserve(len);
        for (int j = 0; j < len; j++) {
            char c = char(rnd.next('A', 'Z'));
            s.push_back(c);
        }
        names[i] = s;
    }

    // Generate queries with a mix of exact bounds, intervals, and random
    vector<int> qs(M);
    for (int i = 0; i < M; i++) {
        int mode = rnd.next(0, 2);
        if (mode == 0) {
            // exact one of the bounds
            int idx = rnd.next(0, N - 1);
            qs[i] = ub[idx];
        } else if (mode == 1 && N > 1) {
            // random in an interval between two consecutive bounds
            int idx = rnd.next(1, N - 1);
            int low = ub[idx - 1] + 1;
            int high = ub[idx];
            if (low <= high) qs[i] = rnd.next(low, high);
            else qs[i] = ub[idx];
        } else {
            // fully random
            qs[i] = rnd.next(0, ub[N - 1]);
        }
    }

    // Output
    println(N, M);
    for (int i = 0; i < N; i++) {
        println(names[i], ub[i]);
    }
    for (int x : qs) {
        println(x);
    }

    return 0;
}

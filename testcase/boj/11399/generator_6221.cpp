#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Generate N biased toward larger small sizes (1..20)
    int N = rnd.wnext(20, 2) + 1;
    // Max possible P_i
    int Pmax = rnd.next(1, 1000);
    // Choose distribution type: 0=increasing,1=random,2=duplicates,3=decreasing
    int type = rnd.next(0, 3);

    vector<int> p(N);
    if (type == 0) {
        // strictly increasing
        int stepMax = max(1, Pmax / max(1, N));
        p[0] = rnd.next(1, stepMax);
        for (int i = 1; i < N; i++) {
            int step = rnd.next(1, stepMax);
            p[i] = min(1000, p[i-1] + step);
        }
    }
    else if (type == 1) {
        // uniform random
        for (int i = 0; i < N; i++)
            p[i] = rnd.next(1, Pmax);
    }
    else if (type == 2) {
        // many duplicates
        int k = rnd.next(1, min(5, N));
        vector<int> vals;
        for (int i = 0; i < k; i++)
            vals.push_back(rnd.next(1, Pmax));
        for (int i = 0; i < N; i++)
            p[i] = rnd.any(vals);
    }
    else {
        // strictly decreasing
        int stepMax = max(1, Pmax / max(1, N));
        vector<int> tmp(N);
        tmp[0] = rnd.next(1, stepMax);
        for (int i = 1; i < N; i++) {
            int step = rnd.next(1, stepMax);
            tmp[i] = min(1000, tmp[i-1] + step);
        }
        // reverse to make decreasing
        for (int i = 0; i < N; i++)
            p[i] = tmp[N-1-i];
    }

    // Occasionally shuffle minorly to introduce small disorder
    if (type == 0 || type == 3) {
        double disturb = rnd.next(0.0, 1.0);
        if (disturb < 0.3) {
            int swaps = rnd.next(1, max(1, N/3));
            for (int i = 0; i < swaps; i++) {
                int a = rnd.next(0, N-1), b = rnd.next(0, N-1);
                swap(p[a], p[b]);
            }
        }
    }

    // Output
    println(N);
    println(p);
    return 0;
}

#include "testlib.h"
#include <vector>
#include <cmath>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Small size
    int N = rnd.next(1, 10);
    int maxH = rnd.next(1, 5);
    // Probability of unknown
    double p_unknown = rnd.next(0, 50) / 100.0;
    int mode = rnd.next(0, 2);
    vector<int> h(N);
    vector<int> deltas = {-1, 0, 1};
    if (mode == 0) {
        // Uniform random heights
        for (int i = 0; i < N; i++) {
            h[i] = rnd.next(0, maxH);
        }
    } else if (mode == 1) {
        // Trend (increasing or decreasing with noise)
        bool inc = rnd.next(0, 1);
        if (inc) {
            h[0] = rnd.next(0, maxH);
            for (int i = 1; i < N; i++) {
                int d = rnd.any(deltas);
                int v = h[i-1] + d;
                if (v < 0) v = 0;
                if (v > maxH) v = maxH;
                h[i] = v;
            }
        } else {
            h[N-1] = rnd.next(0, maxH);
            for (int i = N-2; i >= 0; i--) {
                int d = rnd.any(deltas);
                int v = h[i+1] + d;
                if (v < 0) v = 0;
                if (v > maxH) v = maxH;
                h[i] = v;
            }
        }
    } else {
        // Plateau shape with noise
        int mid = rnd.next(0, N-1);
        int peak = rnd.next(0, maxH);
        for (int i = 0; i < N; i++) {
            int base = peak - abs(i - mid);
            int d = rnd.any(deltas);
            int v = base + d;
            if (v < 0) v = 0;
            if (v > maxH) v = maxH;
            h[i] = v;
        }
    }
    // Randomly hide some entries
    for (int i = 0; i < N; i++) {
        if (rnd.next() < p_unknown) h[i] = -1;
    }
    // Output
    println(N);
    println(h);
    return 0;
}

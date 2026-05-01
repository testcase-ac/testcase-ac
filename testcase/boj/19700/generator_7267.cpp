#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of students
    int N = rnd.next(1, 12);
    // Generate distinct heights
    vector<int> h(N);
    for (int i = 0; i < N; i++) {
        h[i] = 150 + i;
    }
    shuffle(h.begin(), h.end());
    // Occasionally sort heights ascending or descending
    double q = rnd.next();
    if (q < 0.2) {
        sort(h.begin(), h.end());
    } else if (q < 0.4) {
        sort(h.rbegin(), h.rend());
    }
    // Generate k_i values with varied distributions
    vector<int> k(N);
    for (int i = 0; i < N; i++) {
        if (N == 1) {
            k[i] = 1;
        } else {
            double p = rnd.next();
            if (p < 0.15) {
                k[i] = 1;
            } else if (p < 0.3) {
                k[i] = N;
            } else if (p < 0.55) {
                k[i] = rnd.next(1, min(N, 3));
            } else if (p < 0.8) {
                k[i] = rnd.next(max(1, N-2), N);
            } else {
                k[i] = rnd.next(1, N);
            }
        }
    }
    // Output
    println(N);
    for (int i = 0; i < N; i++) {
        println(h[i], k[i]);
    }
    return 0;
}

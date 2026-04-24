#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: size of sequence
    int N = rnd.next(1, 8);
    int M = rnd.next(1, N);

    // Hyper-parameter: probability to duplicate previous values
    double dupProb = rnd.next(0.0, 1.0);
    // Hyper-parameter: maximum value bound choice for diversity
    vector<int> bounds = {5, 10, 10000};
    int maxVal = rnd.any(bounds);
    // Hyper-parameter: whether to sort input numbers
    double sortProb = rnd.next(0.0, 1.0);

    // Generate N numbers with some duplicates
    vector<int> a;
    for (int i = 0; i < N; i++) {
        if (i > 0 && rnd.next() < dupProb) {
            // pick one existing to duplicate
            int idx = rnd.next(0, (int)a.size() - 1);
            a.push_back(a[idx]);
        } else {
            // fresh random value
            a.push_back(rnd.next(1, maxVal));
        }
    }

    // Optionally sort to vary input order
    if (rnd.next() < sortProb) {
        sort(a.begin(), a.end());
    }

    // Output format
    println(N, M);
    println(a);

    return 0;
}

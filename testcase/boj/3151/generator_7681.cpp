#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose number of students
    int N = rnd.next(3, 30);
    vector<int> A;

    // Hyperparameter: embed a few guaranteed zero-sum triples
    int maxTriples = N / 3;
    int tripleCount = rnd.next(0, min(4, maxTriples));
    for (int i = 0; i < tripleCount; ++i) {
        int a, b;
        long long c;
        // generate a + b + c = 0 with c in range
        do {
            a = rnd.next(-10000, 10000);
            b = rnd.next(-10000, 10000);
            c = -(1LL * a + b);
        } while (c < -10000 || c > 10000);
        A.push_back(a);
        A.push_back(b);
        A.push_back((int)c);
    }

    // Extra values: zeros, extremes, duplicates, or random
    vector<int> extremes = {-10000, 10000, -5000, 5000};
    while ((int)A.size() < N) {
        double p = rnd.next();
        if (p < 0.15) {
            // zero to boost zero-sum cases
            A.push_back(0);
        } else if (p < 0.25) {
            // extreme values
            A.push_back(rnd.any(extremes));
        } else if (p < 0.35 && !A.empty()) {
            // duplicate existing to create multi-counts
            A.push_back(rnd.any(A));
        } else {
            // general random biased toward edges or center
            int t = rnd.next(-1, 1);
            int val = rnd.wnext(20001, t) - 10000;
            A.push_back(val);
        }
    }

    // Shuffle to avoid ordered patterns
    shuffle(A.begin(), A.end());

    // Output
    println(N);
    println(A);

    return 0;
}

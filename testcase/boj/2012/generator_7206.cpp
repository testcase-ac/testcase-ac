#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Choose N with bias towards small and medium sizes
    int N;
    double p = rnd.next();
    if (p < 0.1) {
        N = 1;
    } else if (p < 0.4) {
        N = rnd.next(2, 5);
    } else {
        N = rnd.next(6, 20);
    }
    // Prepare possible maximum predicted-rank values
    vector<int> maxOpts = { N, min(500000, N * 2), 500000 };
    int maxA = rnd.any(maxOpts);
    // Choose a distribution type for diversity
    int type = rnd.next(0, 4);
    vector<int> A(N);
    if (type == 0) {
        // All predict rank 1
        for (int i = 0; i < N; i++) A[i] = 1;
    } else if (type == 1) {
        // Nearly ascending with slight noise
        for (int i = 0; i < N; i++) {
            int base = i + 1;
            int delta = rnd.next(-1, 1);
            A[i] = max(1, min(maxA, base + delta));
        }
        sort(A.begin(), A.end());
    } else if (type == 2) {
        // Nearly descending with slight noise
        for (int i = 0; i < N; i++) {
            int base = N - i;
            int delta = rnd.next(-1, 1);
            A[i] = max(1, min(maxA, base + delta));
        }
        sort(A.begin(), A.end(), greater<int>());
    } else if (type == 3) {
        // Uniform in [1, N]
        for (int i = 0; i < N; i++) A[i] = rnd.next(1, N);
    } else {
        // Uniform in [1, maxA] (introduce possible A > N)
        for (int i = 0; i < N; i++) A[i] = rnd.next(1, maxA);
    }
    // Optionally shuffle the input order
    if (rnd.next(0, 1)) {
        shuffle(A.begin(), A.end());
    }
    // Output
    println(N);
    for (int x : A) println(x);
    return 0;
}

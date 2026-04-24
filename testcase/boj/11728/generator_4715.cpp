#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Sample sizes with some bias
    int N = rnd.wnext(10, rnd.next(-1, 1)) + 1;
    int M = rnd.wnext(10, rnd.next(-1, 1)) + 1;

    // Decide if negatives appear
    bool includeNeg = rnd.next(0, 1);
    int L = includeNeg ? rnd.next(-20, -1) : 0;
    int R = rnd.next(max(L + 1, 1), 20);

    // Probability to sample from tails
    double tailProb = rnd.next(0.0, 1.0);

    // Value generator with occasional tail bias
    auto genVal = [&]() {
        if (rnd.next() < tailProb) {
            int t = rnd.next(-2, 2);
            int hi = R - L + 1;
            return rnd.wnext(hi, t) + L;
        } else {
            return rnd.next(L, R);
        }
    };

    // Build arrays and sort them
    vector<int> A(N), B(M);
    for (int i = 0; i < N; i++) A[i] = genVal();
    for (int i = 0; i < M; i++) B[i] = genVal();
    sort(A.begin(), A.end());
    sort(B.begin(), B.end());

    // Output
    println(N, M);
    println(A);
    println(B);

    return 0;
}

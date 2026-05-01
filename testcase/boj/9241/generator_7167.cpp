#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const string alpha = "ACGT";

    // Hyper-parameter for original length bias
    int tN = rnd.any(vector<int>{-2, -1, 0, 1, 2});
    int N = rnd.wnext(15, tN) + 1;  // N in [1,15] with bias
    // Generate original DNA
    string S;
    S.reserve(N);
    for (int i = 0; i < N; i++) {
        S.push_back(rnd.any(alpha));
    }

    // Choose removal segment [l..r]
    int l = rnd.next(0, N - 1);
    int r = rnd.next(l, N - 1);
    int rem_len = l + (N - 1 - r);

    // Hyper-parameter for insertion length bias
    int tL = rnd.any(vector<int>{-2, -1, 0, 1, 2});
    int L = rnd.wnext(16, tL);  // L in [0,15] with bias
    if (rem_len == 0 && L == 0) {
        // Ensure resulting T is non-empty
        L = 1;
    }

    // Generate insertion DNA
    string X;
    X.reserve(L);
    for (int i = 0; i < L; i++) {
        X.push_back(rnd.any(alpha));
    }

    // Build infected DNA T
    string T;
    T.reserve(rem_len + L);
    T += S.substr(0, l);
    T += X;
    if (r + 1 < N) {
        T += S.substr(r + 1);
    }

    // Output
    println(S);
    println(T);

    return 0;
}

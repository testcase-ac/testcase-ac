#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for diversity
    int L = rnd.next(1, 20);               // Length of H
    int K = rnd.next(1, min(L, 10));       // Length of N
    double p = rnd.next();                 // Decide whether to ensure a match

    // Generate random H
    string H;
    H.resize(L);
    for (int i = 0; i < L; i++) {
        H[i] = char(rnd.next('A', 'Z'));
    }

    // Generate N
    string N;
    if (p < 0.4) {
        // Ensure at least one match by taking a substring of H
        int start = rnd.next(0, L - K);
        N = H.substr(start, K);
    } else {
        // Fully random N
        N.resize(K);
        for (int i = 0; i < K; i++) {
            N[i] = char(rnd.next('A', 'Z'));
        }
    }

    // Output
    println(H);
    println(N);
    return 0;
}

#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter for N: sometimes 1, small, or medium
    int N;
    double p = rnd.next();
    if (p < 0.1) {
        N = 1;
    } else if (p < 0.4) {
        N = rnd.next(2, 4);
    } else {
        N = rnd.next(5, 10);
    }
    // Generate initial sequence A[1..N]
    vector<long long> A(N);
    for (int i = 0; i < N; i++) {
        A[i] = rnd.next(1, 100);
    }
    vector<long long> orig = A;
    // Generate a valid sequence of operations and compute T
    vector<int> ops;
    vector<long long> B = A;
    for (int len = N; len > 1; len--) {
        // choose bias t = -1,0,1 to bias wnext
        int t = rnd.any(vector<int>{-1, 0, 1});
        // rnd.wnext(len-1, t) returns [0..len-2], so +1 for [1..len-1]
        int i = rnd.wnext(len - 1, t) + 1;
        ops.push_back(i);
        // apply CON(B, i): B[i-1] = B[i-1] - B[i], erase B[i]
        B[i-1] = B[i-1] - B[i];
        B.erase(B.begin() + i);
    }
    long long T = B[0];
    // Output
    println(N, T);
    println(orig);
    return 0;
}

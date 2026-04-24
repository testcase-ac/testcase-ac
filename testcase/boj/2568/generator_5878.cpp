#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // N between 2 and 15, biased towards smaller
    int N = rnd.wnext(14, -1) + 2;
    // Prepare A positions 1..N
    vector<int> A(N);
    iota(A.begin(), A.end(), 1);
    // Prepare B according to different patterns
    vector<int> B(N);
    int type = rnd.next(0, 3);
    if (type == 0) {
        // Fully random permutation
        B = A;
        shuffle(B.begin(), B.end());
    } else if (type == 1) {
        // Strictly increasing (LIS = N)
        for (int i = 0; i < N; i++) B[i] = i + 1;
    } else if (type == 2) {
        // Strictly decreasing (LIS = 1)
        for (int i = 0; i < N; i++) B[i] = N - i;
    } else {
        // Nearly sorted: small local swaps
        for (int i = 0; i < N; i++) B[i] = i + 1;
        for (int i = 0; i + 1 < N; i++) {
            if (rnd.next() < 0.3) swap(B[i], B[i+1]);
        }
    }
    // Pair up and shuffle input order to break sorted-A assumptions
    vector<pair<int,int>> lines;
    for (int i = 0; i < N; i++) {
        lines.emplace_back(A[i], B[i]);
    }
    shuffle(lines.begin(), lines.end());
    // Output
    println(N);
    for (auto &pr : lines) {
        println(pr.first, pr.second);
    }
    return 0;
}

#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: number of breads
    int n = rnd.next(3, 10);

    // Generate initial permutation A
    vector<int> A(n);
    iota(A.begin(), A.end(), 1);
    shuffle(A.begin(), A.end());

    // Decide whether the case should be possible (even permutation) or impossible (odd)
    bool wantPossible = rnd.next() < 0.5;

    // Function to compute parity of permutation mapping A -> B
    auto parity = [&](const vector<int>& B) {
        vector<int> pos(n + 1);
        for (int i = 0; i < n; i++) pos[A[i]] = i;
        vector<int> C(n);
        for (int i = 0; i < n; i++) C[i] = pos[B[i]];
        int inv = 0;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                if (C[i] > C[j]) inv++;
        return inv % 2;
    };

    // Generate target permutation B with correct parity
    vector<int> B(n);
    while (true) {
        iota(B.begin(), B.end(), 1);
        shuffle(B.begin(), B.end());
        int p = parity(B);
        if ((wantPossible && p == 0) || (!wantPossible && p == 1))
            break;
    }

    // Output the test case
    println(n);
    println(A);
    println(B);
    return 0;
}

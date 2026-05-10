#include "testlib.h"
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

// Helper function to compute number of acorns in boxes 1..x
// according to all rules.
long long count_acorns(const vector<int>& A, const vector<int>& B, const vector<int>& C, int K, int x) {
    long long total = 0;
    for (int i = 0; i < K; ++i) {
        if (x < A[i]) continue;
        int last = min(B[i], x);
        if (last < A[i]) continue;
        // number of boxes: (last - A[i]) / C[i] + 1
        total += (last - A[i]) / C[i] + 1;
    }
    return total;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, K, D
    int N = inf.readInt(1, 1000000, "N");
    inf.readSpace();
    int K = inf.readInt(1, 10000, "K");
    inf.readSpace();
    long long D = inf.readLong(1LL, 1000000000LL, "D");
    inf.readEoln();

    vector<int> A(K), B(K), C(K);

    for (int i = 0; i < K; ++i) {
        int a = inf.readInt(1, N, "A_i");
        inf.readSpace();
        int b = inf.readInt(a, N, "B_i");
        inf.readSpace();
        int c = inf.readInt(1, a, "C_i");
        inf.readEoln();

        ensuref(a <= b, "A_i (%d) > B_i (%d) at rule %d", a, b, i+1);
        ensuref(c >= 1 && c <= a, "C_i (%d) not in [1, A_i (%d)] at rule %d", c, a, i+1);

        A[i] = a;
        B[i] = b;
        C[i] = c;
    }

    // Global constraint: D <= total number of acorns that can be placed
    long long total_possible = count_acorns(A, B, C, K, N);
    ensuref(D <= total_possible, "D (%lld) is greater than total possible acorns (%lld)", D, total_possible);

    inf.readEof();
}

#include "testlib.h"
#include <vector>
#include <algorithm>
#include <cstdint>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(2, 11, "N");
    inf.readEoln();

    // Read sequence A of size N
    vector<int> A = inf.readInts(N, 1, 100, "A");
    inf.readEoln();

    // Read operator counts: plus, minus, multiply, divide
    int plus_cnt = inf.readInt(0, N-1, "plus");
    inf.readSpace();
    int minus_cnt = inf.readInt(0, N-1, "minus");
    inf.readSpace();
    int mul_cnt = inf.readInt(0, N-1, "mul");
    inf.readSpace();
    int div_cnt = inf.readInt(0, N-1, "div");
    inf.readEoln();

    // Check sum of operator counts
    int total_ops = plus_cnt + minus_cnt + mul_cnt + div_cnt;
    ensuref(total_ops == N-1,
            "Sum of operators must be N-1, but got %d (expected %d)",
            total_ops, N-1);

    // Prepare operator multiset: 0:+, 1:-, 2:*, 3:/
    vector<int> ops;
    ops.reserve(N-1);
    for (int i = 0; i < plus_cnt; ++i) ops.push_back(0);
    for (int i = 0; i < minus_cnt; ++i) ops.push_back(1);
    for (int i = 0; i < mul_cnt; ++i) ops.push_back(2);
    for (int i = 0; i < div_cnt; ++i) ops.push_back(3);

    // Global invariant: for any arrangement of these operators,
    // the intermediate and final results must lie in [-1e9, 1e9].
    const int64_t MINV = -1000000000LL;
    const int64_t MAXV =  1000000000LL;

    // Sort and iterate all unique permutations
    sort(ops.begin(), ops.end());
    do {
        int64_t curr = A[0];
        // Step through the N-1 operations
        for (int i = 1; i < N; ++i) {
            int op = ops[i-1];
            int64_t b = A[i];
            if (op == 0) {
                curr += b;
            } else if (op == 1) {
                curr -= b;
            } else if (op == 2) {
                curr *= b;
            } else { // op == 3, division
                // Ai >= 1 guaranteed
                if (curr >= 0) {
                    curr = curr / b;
                } else {
                    curr = - ( ( -curr ) / b );
                }
            }
            ensuref(curr >= MINV && curr <= MAXV,
                    "Value %lld out of allowed range [%lld, %lld] at step %d for operator sequence",
                    curr, MINV, MAXV, i);
        }
        // final curr also checked by above
    } while (next_permutation(ops.begin(), ops.end()));

    inf.readEof();
    return 0;
}

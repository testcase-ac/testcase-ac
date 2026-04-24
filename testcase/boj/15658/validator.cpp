#include "testlib.h"
#include <vector>
#include <cassert>
using namespace std;

static const int LIMIT = 1000000000;
int N;
vector<int> A;
int cnt_ops[4];

void dfs_check(int pos, long long value, int rem[4]) {
    // pos = number of operations performed so far; value = current result
    if (pos == N - 1) {
        // final result check
        ensuref(value >= -LIMIT && value <= LIMIT,
                "Final result %lld out of bounds [%d, %d]", value, -LIMIT, LIMIT);
        return;
    }
    // next operand is A[pos+1]
    long long b = A[pos + 1];
    for (int t = 0; t < 4; ++t) {
        if (rem[t] > 0) {
            int nxt_rem[4] = { rem[0], rem[1], rem[2], rem[3] };
            --nxt_rem[t];
            long long nv;
            if (t == 0) {
                // addition
                nv = value + b;
            } else if (t == 1) {
                // subtraction
                nv = value - b;
            } else if (t == 2) {
                // multiplication
                nv = value * b;
            } else {
                // division, C++14 style
                // b >= 1 by constraints, so no div by zero
                if (value >= 0) {
                    nv = value / b;
                } else {
                    nv = - ( ( -value ) / b );
                }
            }
            ensuref(nv >= -LIMIT && nv <= LIMIT,
                    "Intermediate result %lld out of bounds [%d, %d] at operation index %d",
                    nv, -LIMIT, LIMIT, pos + 1);
            dfs_check(pos + 1, nv, nxt_rem);
        }
    }
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    N = inf.readInt(2, 11, "N");
    inf.readEoln();

    // Read sequence A_i
    A = inf.readInts(N, 1, 100, "A_i");
    inf.readEoln();

    // Read operator counts: +, -, *, /
    vector<int> tmp = inf.readInts(4, 0, 4 * N, "op_cnt");
    inf.readEoln();
    for (int i = 0; i < 4; i++) {
        cnt_ops[i] = tmp[i];
    }
    long long sum_ops = 0;
    for (int i = 0; i < 4; i++) sum_ops += cnt_ops[i];
    ensuref(sum_ops >= N - 1,
            "Sum of operator counts %lld is less than N-1 = %d", sum_ops, N-1);
    ensuref(sum_ops <= 4LL * N,
            "Sum of operator counts %lld exceeds 4*N = %d", sum_ops, 4*N);

    // Check the global guarantee: for every way to insert N-1 operators
    // from the given multiset, the intermediate and final results
    // stay within [-1e9,1e9].
    int rem[4] = { cnt_ops[0], cnt_ops[1], cnt_ops[2], cnt_ops[3] };
    dfs_check(0, A[0], rem);

    inf.readEof();
    return 0;
}

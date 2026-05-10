#include "testlib.h"
#include <vector>
#include <numeric>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N and M
    int N = inf.readInt(2, 500000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 500000, "M");
    inf.readEoln();

    // 2. Read w_1 ... w_{N-1}
    vector<int> w(N-1);
    for (int i = 0; i < N-1; ++i) {
        w[i] = inf.readInt(1, 1000000000, "w_i");
        if (i < N-2) inf.readSpace();
    }
    inf.readEoln();

    // 3. Read M lines: u_j, v_j, x_j
    long long sum_x = 0;
    for (int j = 0; j < M; ++j) {
        int u = inf.readInt(1, N-1, "u_j");
        inf.readSpace();
        int v = inf.readInt(u+1, N, "v_j"); // u < v <= N
        inf.readSpace();
        int x = inf.readInt(1, 1000000000, "x_j");
        inf.readEoln();

        sum_x += x;
        ensuref(sum_x <= 1000000000LL, "Sum of all x_j exceeds 1e9 at line %d (current sum: %lld)", j+3, sum_x);
    }

    inf.readEof();
}

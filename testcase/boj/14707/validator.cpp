#include "testlib.h"
#include <vector>
#include <cassert>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAX_NML = 123456;
    const long long MAX_SUM = 1000000000LL;

    int N = inf.readInt(1, MAX_NML, "N");
    inf.readSpace();
    int M = inf.readInt(1, MAX_NML, "M");
    inf.readSpace();
    int L = inf.readInt(1, MAX_NML, "L");
    inf.readEoln();

    vector<long long> H(N);
    long long sumH = 0;
    for (int i = 0; i < N; ++i) {
        H[i] = inf.readLong(1LL, MAX_SUM, "H_i");
        if (i + 1 < N) inf.readSpace();
        // accumulate with higher precision to avoid overflow in validation
        sumH += H[i];
        ensuref(sumH <= MAX_SUM,
                "Sum of H_i exceeds 1e9 after index %d (current sum = %lld)", i + 1, sumH);
    }
    inf.readEoln();

    vector<long long> W(M);
    long long sumW = 0;
    for (int j = 0; j < M; ++j) {
        W[j] = inf.readLong(1LL, MAX_SUM, "W_j");
        if (j + 1 < M) inf.readSpace();
        sumW += W[j];
        ensuref(sumW <= MAX_SUM,
                "Sum of W_j exceeds 1e9 after index %d (current sum = %lld)", j + 1, sumW);
    }
    inf.readEoln();

    // No further global properties are guaranteed by the statement:
    // - No constraints about total area fitting into a specific type.
    // - No constraints about color usage distribution other than cycling pattern,
    //   which is determined algorithmically and not an input precondition.
    // Therefore we don't simulate coloring here.

    inf.readEof();
}

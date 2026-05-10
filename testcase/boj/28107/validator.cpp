#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int N_MAX = 100000;
    const int M_MAX = 200000;
    const int TYPE_MAX = 200000;

    int N = inf.readInt(1, N_MAX, "N");
    inf.readSpace();
    int M = inf.readInt(1, M_MAX, "M");
    inf.readEoln();

    long long totalK = 0;
    for (int i = 0; i < N; ++i) {
        // read k
        int k = inf.readInt(0, TYPE_MAX, "k");
        totalK += k;
        ensuref(totalK <= 200000LL, "Sum of all k must be <= 200000, but current sum is %lld", totalK);

        vector<int> A;
        A.reserve(k);

        for (int j = 0; j < k; ++j) {
            inf.readSpace();
            int aij = inf.readInt(1, TYPE_MAX, "A_ij");
            A.push_back(aij);
        }
        inf.readEoln();

        // Check that all A_i in this customer's list are distinct
        if (k > 1) {
            sort(A.begin(), A.end());
            for (int j = 1; j < k; ++j) {
                ensuref(A[j] != A[j - 1],
                        "Customer %d has duplicate sushi type %d in order list",
                        i + 1, A[j]);
            }
        }
    }

    // Read the M sushi types B_1..B_M
    if (M > 0) {
        int b = inf.readInt(1, TYPE_MAX, "B_1");
        for (int i = 1; i < M; ++i) {
            inf.readSpace();
            b = inf.readInt(1, TYPE_MAX, "B_i");
        }
    }
    inf.readEoln();

    inf.readEof();
}

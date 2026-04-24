#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and K
    int N = inf.readInt(1, 1000000, "N");
    inf.readSpace();
    int K = inf.readInt(1, 1000000, "K");
    inf.readEoln();

    // Read the K jump values X_i
    // Each X_i must satisfy 1 <= X_i < N
    // If N == 1, then the range [1, N-1] is empty; but since K >= 1, tests will avoid N == 1
    inf.readInts(K, 1, N - 1, "X");
    inf.readEoln();

    // Read Q
    int Q = inf.readInt(1, 1000000, "Q");
    inf.readEoln();

    // Read each query [L, R]
    for (int i = 0; i < Q; i++) {
        int L = inf.readInt(0, N - 1, "L");
        inf.readSpace();
        int R = inf.readInt(0, N - 1, "R");
        inf.readEoln();
        ensuref(L <= R,
                "For query %d, expected L <= R but got L=%d, R=%d",
                i, L, R);
    }

    inf.readEof();
    return 0;
}

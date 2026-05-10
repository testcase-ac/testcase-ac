#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // First line: N, M, K, T
    int N = inf.readInt(1, 300000, "N");
    inf.readSpace();
    int M = inf.readInt(N - 1, 300000, "M");
    inf.readSpace();
    int K = inf.readInt(1, N, "K");
    inf.readSpace();
    int T = inf.readInt(1, N, "T");
    inf.readEoln();

    // Second line: K strictly increasing a_i
    vector<int> a(K);
    a = inf.readInts(K, 1, N, "a_i");
    inf.readEoln();
    for (int i = 1; i < K; i++) {
        ensuref(a[i-1] < a[i],
                "a_i not strictly increasing at index %d: %d >= %d",
                i, a[i-1], a[i]);
    }

    // Next T lines: farms b_i and price c_i, b_i strictly increasing
    vector<int> b(T);
    for (int i = 0; i < T; i++) {
        b[i] = inf.readInt(1, N, "b_i");
        inf.readSpace();
        inf.readInt(1, 1000000000, "c_i");
        inf.readEoln();
        if (i > 0) {
            ensuref(b[i-1] < b[i],
                    "b_i not strictly increasing at index %d: %d >= %d",
                    i, b[i-1], b[i]);
        }
    }

    // Next M lines: edges u_i, v_i, w_i with u_i < v_i
    for (int i = 0; i < M; i++) {
        int u = inf.readInt(1, N, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, N, "v_i");
        ensuref(u < v, "Edge endpoints not ordered at edge %d: u=%d, v=%d", i, u, v);
        inf.readSpace();
        inf.readInt(1, 1000000000, "w_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}

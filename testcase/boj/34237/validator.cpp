#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // N: number of cubs (bets), M: number of past years
    int N = inf.readInt(1, 50, "N");
    inf.readSpace();
    int M = inf.readInt(1, 100000, "M");
    inf.readEoln();

    vector<int> a(N), b(N);

    // Read bets: 0 <= b_i <= a_i <= 100, a_i + b_i <= 100
    for (int i = 0; i < N; ++i) {
        a[i] = inf.readInt(0, 100, "a_i");
        inf.readSpace();
        b[i] = inf.readInt(0, 100, "b_i");
        inf.readEoln();

        ensuref(b[i] <= a[i],
                "Bet constraint violated at i=%d: need b_i <= a_i, got a_i=%d, b_i=%d",
                i + 1, a[i], b[i]);
        ensuref((long long)a[i] + (long long)b[i] <= 100,
                "Bet sum constraint violated at i=%d: a_i + b_i <= 100, got %d + %d",
                i + 1, a[i], b[i]);
    }

    // Read matches: 0 <= y_j <= x_j, 0 <= x_j + y_j <= g_j <= 100
    for (int j = 0; j < M; ++j) {
        int g = inf.readInt(0, 100, "g_j");
        inf.readSpace();
        int x = inf.readInt(0, 100, "x_j");
        inf.readSpace();
        int y = inf.readInt(0, 100, "y_j");
        inf.readEoln();

        ensuref(y <= x,
                "Score ordering violated at j=%d: require y_j <= x_j, got x_j=%d, y_j=%d",
                j + 1, x, y);
        ensuref((long long)x + (long long)y <= g,
                "Score sum constraint violated at j=%d: require x_j + y_j <= g_j, "
                "got x_j=%d, y_j=%d, g_j=%d",
                j + 1, x, y, g);
    }

    inf.readEof();
}

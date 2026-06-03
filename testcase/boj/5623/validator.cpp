#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 1000, "N");
    inf.readEoln();

    vector<vector<int>> s(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (j > 0) {
                inf.readSpace();
            }
            int low = (i == j ? 0 : 1);
            int high = (i == j ? 0 : 100000);
            s[i][j] = inf.readInt(low, high, "S_ij");
        }
        inf.readEoln();
    }
    inf.readEof();

    if (n == 2) {
        ensuref(s[0][1] == 2 && s[1][0] == 2,
                "N=2 has a unique positive sequence only when both off-diagonal sums are 2");
        return 0;
    }

    int numerator = s[0][1] + s[0][2] - s[1][2];
    ensuref(numerator > 0 && numerator % 2 == 0,
            "A[1] must be a positive integer, numerator=%d", numerator);

    vector<int> a(n);
    a[0] = numerator / 2;
    ensuref(a[0] > 0, "A[1] must be positive, got %d", a[0]);

    for (int i = 1; i < n; ++i) {
        a[i] = s[0][i] - a[0];
        ensuref(a[i] > 0, "A[%d] must be positive, got %d", i + 1, a[i]);
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int expected = (i == j ? 0 : a[i] + a[j]);
            ensuref(s[i][j] == expected,
                    "S[%d][%d]=%d, expected %d from the unique positive sequence",
                    i + 1, j + 1, s[i][j], expected);
        }
    }
}

#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 2000, "N");
    inf.readEoln();

    vector<vector<int>> a(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int low = (i == j ? 0 : 1);
            int high = (i == j ? 0 : 1000000);
            a[i][j] = inf.readInt(low, high, "A_ij");

            if (j + 1 == n) {
                inf.readEoln();
            } else {
                inf.readSpace();
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            ensuref(a[i][j] == a[j][i],
                    "matrix is not symmetric at (%d, %d): %d != %d",
                    i + 1, j + 1, a[i][j], a[j][i]);
        }
    }

    inf.readEof();
}

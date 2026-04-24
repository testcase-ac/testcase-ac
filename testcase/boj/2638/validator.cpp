#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read dimensions
    int N = inf.readInt(5, 100, "N");
    inf.readSpace();
    int M = inf.readInt(5, 100, "M");
    inf.readEoln();

    // Read grid
    vector<vector<int>> a(N, vector<int>(M));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            a[i][j] = inf.readInt(0, 1, "A");
            if (j + 1 < M) inf.readSpace();
        }
        inf.readEoln();
    }

    // Validate that no cheese is on the boundary
    for (int j = 0; j < M; j++) {
        ensuref(a[0][j] == 0, "Cheese found on top border at (0,%d)", j);
        ensuref(a[N-1][j] == 0, "Cheese found on bottom border at (%d,%d)", N-1, j);
    }
    for (int i = 0; i < N; i++) {
        ensuref(a[i][0] == 0, "Cheese found on left border at (%d,0)", i);
        ensuref(a[i][M-1] == 0, "Cheese found on right border at (%d,%d)", i, M-1);
    }

    inf.readEof();
    return 0;
}

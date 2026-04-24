#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read exactly 9 lines, each with exactly 9 digits [0-9]
    vector<string> rows(9);
    for (int i = 0; i < 9; i++) {
        rows[i] = inf.readToken("[0-9]{9}", "row");
        inf.readEoln();
    }

    // Parse into integers
    int a[9][9];
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            a[i][j] = rows[i][j] - '0';
        }
    }

    // Check no duplicates in each row (ignoring zeros)
    for (int i = 0; i < 9; i++) {
        bool seen[10] = {false};
        for (int j = 0; j < 9; j++) {
            int v = a[i][j];
            if (v == 0) continue;
            ensuref(v >= 1 && v <= 9,
                    "Invalid digit %d at row %d, col %d", v, i+1, j+1);
            ensuref(!seen[v],
                    "Duplicate digit %d in row %d", v, i+1);
            seen[v] = true;
        }
    }

    // Check no duplicates in each column
    for (int j = 0; j < 9; j++) {
        bool seen[10] = {false};
        for (int i = 0; i < 9; i++) {
            int v = a[i][j];
            if (v == 0) continue;
            ensuref(!seen[v],
                    "Duplicate digit %d in column %d", v, j+1);
            seen[v] = true;
        }
    }

    // Check no duplicates in each 3x3 block
    for (int bi = 0; bi < 3; bi++) {
        for (int bj = 0; bj < 3; bj++) {
            bool seen[10] = {false};
            for (int di = 0; di < 3; di++) {
                for (int dj = 0; dj < 3; dj++) {
                    int i = bi*3 + di;
                    int j = bj*3 + dj;
                    int v = a[i][j];
                    if (v == 0) continue;
                    ensuref(!seen[v],
                            "Duplicate digit %d in block starting at row %d, col %d",
                            v, bi*3+1, bj*3+1);
                    seen[v] = true;
                }
            }
        }
    }

    inf.readEof();
    return 0;
}

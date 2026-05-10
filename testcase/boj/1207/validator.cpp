#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read L
    int L = inf.readInt(3, 10, "L");
    inf.readEoln();

    // For each of 5 pieces
    for (int piece = 0; piece < 5; ++piece) {
        // Read N, M
        int N = inf.readInt(1, L, "N");
        inf.readSpace();
        int M = inf.readInt(1, L, "M");
        inf.readEoln();

        vector<string> grid(N);
        for (int i = 0; i < N; ++i) {
            grid[i] = inf.readLine("[#\\.]{"+to_string(M)+","+to_string(M)+"}", "piece_row");
            ensuref((int)grid[i].size() == M, "Row %d of piece %d has wrong length: %d (expected %d)", i+1, piece+1, (int)grid[i].size(), M);
            for (char c : grid[i]) {
                ensuref(c == '#' || c == '.', "Invalid character '%c' in piece %d row %d", c, piece+1, i+1);
            }
        }

        // Check that first and last row have at least one '#'
        bool first_row_has = false, last_row_has = false;
        for (int j = 0; j < M; ++j) {
            if (grid[0][j] == '#') first_row_has = true;
            if (grid[N-1][j] == '#') last_row_has = true;
        }
        ensuref(first_row_has, "First row of piece %d does not have any '#'", piece+1);
        ensuref(last_row_has, "Last row of piece %d does not have any '#'", piece+1);

        // Check that first and last column have at least one '#'
        bool first_col_has = false, last_col_has = false;
        for (int i = 0; i < N; ++i) {
            if (grid[i][0] == '#') first_col_has = true;
            if (grid[i][M-1] == '#') last_col_has = true;
        }
        ensuref(first_col_has, "First column of piece %d does not have any '#'", piece+1);
        ensuref(last_col_has, "Last column of piece %d does not have any '#'", piece+1);
    }

    inf.readEof();
}

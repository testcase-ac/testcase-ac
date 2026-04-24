#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read and validate N, M
    int N = inf.readInt(1, 50, "N");
    inf.readSpace();
    int M = inf.readInt(1, 50, "M");
    inf.readEoln();

    // Read and validate each of the N rows
    for (int i = 0; i < N; i++) {
        // Read the full line (any characters), then check length and allowed chars
        string row = inf.readLine("[^]+", "row_" + to_string(i+1));
        ensuref((int)row.size() == M,
                "Row %d has length %d but expected %d", i+1, (int)row.size(), M);
        for (int j = 0; j < M; j++) {
            char c = row[j];
            bool ok = (c == 'A' || c == 'B' || c == 'C' || c == 'D' || c == 'F');
            ensuref(ok,
                    "Invalid character '%c' at row %d, column %d: must be one of A, B, C, D, F",
                    c, i+1, j+1);
        }
    }

    // The file should end immediately after the last row
    inf.readEof();
    return 0;
}

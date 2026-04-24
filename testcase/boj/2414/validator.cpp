#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 50, "N");
    inf.readSpace();
    int M = inf.readInt(1, 50, "M");
    inf.readEoln();

    // Read the board rows
    for (int i = 0; i < N; i++) {
        // Read an entire line (may contain any chars), then validate
        string row = inf.readLine("[^]+", "row");
        // Check exact length
        ensuref((int)row.size() == M,
                "Row %d: expected length %d, found %d",
                i+1, M, (int)row.size());
        // Check each character
        for (int j = 0; j < M; j++) {
            char c = row[j];
            ensuref(c == '.' || c == '*',
                    "Row %d, column %d: invalid character '%c', expected '.' or '*'",
                    i+1, j+1, c);
        }
    }

    // Ensure no extra data after the grid
    inf.readEof();
    return 0;
}

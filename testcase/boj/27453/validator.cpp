#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, M, K
    int N = inf.readInt(2, 1000, "N");
    inf.readSpace();
    int M = inf.readInt(2, 1000, "M");
    inf.readSpace();
    int K = inf.readInt(0, 27, "K");
    inf.readEoln();

    // Read grid rows
    int countS = 0, countH = 0;
    for (int i = 0; i < N; i++) {
        // Read the entire row (no EOLN) as a raw string
        string row = inf.readLine("[^]+", "grid_row");
        // Check exact length M
        ensuref((int)row.size() == M,
                "Row %d: expected length %d, found %d", i+1, M, (int)row.size());
        // Validate characters and count S/H
        for (int j = 0; j < M; j++) {
            char c = row[j];
            if (c == 'S') {
                countS++;
            } else if (c == 'H') {
                countH++;
            } else if (c == 'X') {
                // wall, OK
            } else if (c >= '0' && c <= '9') {
                // misfortune count, OK
            } else {
                ensuref(false,
                        "Row %d, column %d: invalid character '%c'", 
                        i+1, j+1, c);
            }
        }
    }

    // Exactly one school 'S' and one home 'H'
    ensuref(countS == 1, "Expected exactly one 'S', found %d", countS);
    ensuref(countH == 1, "Expected exactly one 'H', found %d", countH);

    inf.readEof();
    return 0;
}

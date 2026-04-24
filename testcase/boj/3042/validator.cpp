#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(3, 100, "N");
    inf.readEoln();

    vector<bool> seen(26, false);
    for (int i = 0; i < N; i++) {
        // Read each row as a full line
        string row = inf.readLine("[^]+", "row");
        // Check row length
        ensuref((int)row.size() == N,
                "Row %d has invalid length %d (expected %d)",
                i+1, (int)row.size(), N);
        // Check characters and letter uniqueness
        for (int j = 0; j < N; j++) {
            char c = row[j];
            ensuref(c == '.' || (c >= 'A' && c <= 'Z'),
                    "Row %d, column %d: invalid character '%c'",
                    i+1, j+1, c);
            if (c >= 'A' && c <= 'Z') {
                int idx = c - 'A';
                ensuref(!seen[idx],
                        "Duplicate letter '%c' found at row %d, column %d",
                        c, i+1, j+1);
                seen[idx] = true;
            }
        }
    }

    inf.readEof();
    return 0;
}

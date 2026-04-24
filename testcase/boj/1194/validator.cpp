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

    // Counters for '0' and '1'
    int count0 = 0;
    int count1 = 0;

    // Read each row
    for (int i = 0; i < N; i++) {
        // Read the entire line (may contain any chars), then validate
        string row = inf.readLine("[^]+", "row");
        // Check length
        ensuref((int)row.size() == M,
                "Row %d has length %d but expected %d", i+1, (int)row.size(), M);
        // Check each character
        for (int j = 0; j < M; j++) {
            char c = row[j];
            bool ok = false;
            // Empty cell or wall
            if (c == '.' || c == '#') ok = true;
            // Start or exit
            else if (c == '0') { ok = true; count0++; }
            else if (c == '1') { ok = true; count1++; }
            // Keys a-f
            else if (c >= 'a' && c <= 'f') ok = true;
            // Doors A-F
            else if (c >= 'A' && c <= 'F') ok = true;
            if (!ok) {
                ensuref(ok, "Invalid character '%c' at row %d, column %d", c, i+1, j+1);
            }
        }
    }

    // Validate counts of start and exit
    ensuref(count0 == 1,
            "There must be exactly one start '0' but found %d", count0);
    ensuref(count1 >= 1,
            "There must be at least one exit '1' but found %d", count1);

    inf.readEof();
    return 0;
}

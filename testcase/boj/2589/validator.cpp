#include "testlib.h"
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read dimensions
    int H = inf.readInt(1, 50, "H");
    inf.readSpace();
    int W = inf.readInt(1, 50, "W");
    inf.readEoln();

    // Read the map
    int land_count = 0;
    for (int i = 0; i < H; i++) {
        // Read the i-th row: allow any chars, then check length and content
        string row = inf.readLine("[^]+", "row");
        ensuref((int)row.size() == W,
                "Row %d length must be exactly %d, found %d",
                i+1, W, (int)row.size());
        for (int j = 0; j < W; j++) {
            char c = row[j];
            ensuref(c == 'L' || c == 'W',
                    "Invalid character at row %d, column %d: expected 'L' or 'W', found '%c'",
                    i+1, j+1, c);
            if (c == 'L') land_count++;
        }
    }

    // There must be at least two land cells to have a valid treasure path
    ensuref(land_count >= 2,
            "The map must contain at least two land cells, found %d",
            land_count);

    inf.readEof();
    return 0;
}

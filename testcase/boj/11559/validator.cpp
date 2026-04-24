#include "testlib.h"
#include <vector>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // There is exactly one test: exactly 12 lines follow
    const int ROWS = 12;
    const int COLS = 6;
    vector<string> grid(ROWS);

    // Read each of the 12 rows
    for (int i = 0; i < ROWS; i++) {
        // Each line must consist of exactly 6 characters among '.', 'R','G','B','P','Y'
        string rowName = "row_" + to_string(i+1);
        grid[i] = inf.readLine("[.RGBPY]{6}", rowName.c_str());
    }

    // Validate gravity: no puyo may have an empty cell directly below it
    for (int i = 0; i + 1 < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            char c = grid[i][j];
            if (c != '.' && grid[i+1][j] == '.') {
                // Floating puyo detected
                ensuref(false,
                        "Floating puyo at row %d, col %d: '%c' has empty below",
                        i+1, j+1, c);
            }
        }
    }

    // No extra content
    inf.readEof();
    return 0;
}

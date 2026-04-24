#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read R and C
    int R = inf.readInt(2, 20, "R");
    inf.readSpace();
    int C = inf.readInt(2, 20, "C");
    inf.readEoln();

    // Read the grid
    vector<string> grid(R);
    string regexRow = string("[a-z#]{") + to_string(C) + "," + to_string(C) + "}";
    for (int i = 0; i < R; i++) {
        // Each row is exactly C characters, each either lowercase letter or '#'
        grid[i] = inf.readToken(regexRow, "grid_row_" + to_string(i));
        inf.readEoln();
    }

    // Check that there is at least one valid word (segment of length >= 2)
    bool hasWord = false;

    // Check horizontal segments
    for (int i = 0; i < R && !hasWord; i++) {
        int len = 0;
        for (int j = 0; j < C; j++) {
            if (grid[i][j] != '#') {
                len++;
            } else {
                if (len >= 2) { hasWord = true; break; }
                len = 0;
            }
        }
        if (len >= 2) hasWord = true;
    }

    // Check vertical segments
    for (int j = 0; j < C && !hasWord; j++) {
        int len = 0;
        for (int i = 0; i < R; i++) {
            if (grid[i][j] != '#') {
                len++;
            } else {
                if (len >= 2) { hasWord = true; break; }
                len = 0;
            }
        }
        if (len >= 2) hasWord = true;
    }

    ensuref(hasWord, "No contiguous segment of letters of length >= 2 found");

    inf.readEof();
    return 0;
}

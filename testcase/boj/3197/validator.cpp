#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read R and C
    int R = inf.readInt(1, 1500, "R");
    inf.readSpace();
    int C = inf.readInt(1, 1500, "C");
    inf.readEoln();

    // Prepare a regex for each row: exactly C characters among '.', 'X', 'L'
    string row_regex = string("[.XL]{") + to_string(C) + "}";

    // Read the grid and count the 'L' occurrences
    int swan_count = 0;
    for (int i = 0; i < R; i++) {
        // Read one line of length exactly C
        string row = inf.readLine(row_regex.c_str(), "row");
        // Count swans in this row
        for (int j = 0; j < C; j++) {
            if (row[j] == 'L') swan_count++;
        }
    }

    // Exactly two swans must be present
    ensuref(swan_count == 2, "There must be exactly 2 'L' characters, found %d", swan_count);

    inf.readEof();
    return 0;
}

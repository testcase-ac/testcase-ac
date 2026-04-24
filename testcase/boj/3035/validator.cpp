#include "testlib.h"
#include <string>
#include <cctype>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read and validate R, C, ZR, ZC
    int R = inf.readInt(1, 50, "R");
    inf.readSpace();
    int C = inf.readInt(1, 50, "C");
    inf.readSpace();
    int ZR = inf.readInt(1, 5, "ZR");
    inf.readSpace();
    int ZC = inf.readInt(1, 5, "ZC");
    inf.readEoln();

    // Read and validate each of the R rows
    for (int i = 0; i < R; i++) {
        // Read the next token (row string)
        string row = inf.readToken("[^]+", "row");
        // Check exact length C
        ensuref((int)row.size() == C,
                "Row %d has length %d, but expected %d",
                i + 1, (int)row.size(), C);
        // Check each character is alphanumeric or '.'
        for (int j = 0; j < C; j++) {
            char ch = row[j];
            bool ok = (isalnum(static_cast<unsigned char>(ch)) || ch == '.');
            ensuref(ok,
                    "Invalid character '%c' at row %d, column %d: must be alphanumeric or '.'",
                    ch, i + 1, j + 1);
        }
        inf.readEoln();
    }

    // No extra content
    inf.readEof();
    return 0;
}

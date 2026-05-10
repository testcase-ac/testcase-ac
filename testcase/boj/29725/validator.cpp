#include "testlib.h"
#include <set>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // The allowed characters for each cell
    set<char> allowed = {'.', 'K', 'k', 'P', 'p', 'N', 'n', 'B', 'b', 'R', 'r', 'Q', 'q'};

    // There must be exactly 8 lines
    for (int row = 0; row < 8; ++row) {
        string line = inf.readLine("[^]+", "chessboard row");
        ensuref((int)line.size() == 8, "Row %d does not have exactly 8 characters (has %d)", row+1, (int)line.size());
        for (int col = 0; col < 8; ++col) {
            char c = line[col];
            ensuref(allowed.count(c), "Invalid character '%c' at row %d, column %d", c, row+1, col+1);
        }
    }

    inf.readEof();
}

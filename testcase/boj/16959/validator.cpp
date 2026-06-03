#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 10, "N");
    inf.readEoln();

    vector<bool> seen(n * n + 1, false);
    for (int row = 0; row < n; ++row) {
        for (int col = 0; col < n; ++col) {
            if (col > 0) {
                inf.readSpace();
            }

            int value = inf.readInt(1, n * n, "board_i_j");
            ensuref(!seen[value], "duplicate board value at row %d column %d: %d",
                    row + 1, col + 1, value);
            seen[value] = true;
        }
        inf.readEoln();
    }

    inf.readEof();
}

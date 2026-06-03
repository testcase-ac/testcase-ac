#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int r = inf.readInt(1, 500, "R");
    inf.readSpace();
    int c = inf.readInt(1, 500, "C");
    inf.readEoln();

    vector<bool> seen(300001, false);
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            if (j > 0) {
                inf.readSpace();
            }
            int value = inf.readInt(0, 300000, "A_ij");
            ensuref(!seen[value], "duplicate board value at row %d column %d: %d", i + 1, j + 1, value);
            seen[value] = true;
        }
        inf.readEoln();
    }

    inf.readEof();
}

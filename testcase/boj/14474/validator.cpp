#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int h = inf.readInt(1, 1000, "H");
    inf.readSpace();
    int w = inf.readInt(1, 1000, "W");
    inf.readEoln();

    int cells = h * w;
    vector<bool> seen(cells + 1, false);

    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            if (j > 0) {
                inf.readSpace();
            }

            int elevation = inf.readInt(1, cells, "M_i_j");
            ensuref(!seen[elevation],
                    "duplicate elevation %d at row %d column %d",
                    elevation,
                    i + 1,
                    j + 1);
            seen[elevation] = true;
        }
        inf.readEoln();
    }

    inf.readEof();
}

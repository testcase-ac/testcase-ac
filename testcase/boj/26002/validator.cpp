#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int h = inf.readInt(2, 40, "h");
    inf.readSpace();
    int w = inf.readInt(2, 40, "w");
    inf.readEoln();

    int n = h * w;
    vector<bool> seen(n + 1, false);
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            if (j > 0) {
                inf.readSpace();
            }

            int value = inf.readInt(1, n, "a_ij");
            ensuref(!seen[value],
                    "duplicate plot number at row %d column %d: %d",
                    i + 1,
                    j + 1,
                    value);
            seen[value] = true;
        }
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}

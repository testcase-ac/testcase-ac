#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int m = inf.readInt(1, 1000000, "m");
    inf.readEoln();

    vector<int> b = inf.readInts(m, 1, m, "b_i");
    inf.readEoln();

    for (int i = 0; i < m;) {
        int height = b[i];
        ensuref(i + height <= m,
                "run starting at position %d with height %d exceeds m=%d",
                i + 1, height, m);

        for (int j = i; j < i + height; ++j) {
            ensuref(b[j] == height,
                    "position %d has value %d, expected %d for run starting at position %d",
                    j + 1, b[j], height, i + 1);
        }

        i += height;
    }

    inf.readEof();
}

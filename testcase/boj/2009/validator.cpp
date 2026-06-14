#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "n");
    inf.readEoln();

    for (int grid = 0; grid < 3; ++grid) {
        for (int row = 0; row < n; ++row) {
            string value = inf.readToken("[01]{1,100}", "grid_row");
            ensuref((int)value.size() == n,
                    "grid %d row %d has length %d, expected %d",
                    grid + 1, row + 1, (int)value.size(), n);
            inf.readEoln();
        }
    }

    inf.readEof();
}

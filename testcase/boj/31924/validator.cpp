#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "N");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        string row = inf.readLine("[A-Z]{1,100}", "grid_row");
        ensuref(static_cast<int>(row.size()) == n,
                "grid row %d has length %d, expected %d",
                i + 1,
                static_cast<int>(row.size()),
                n);
    }

    inf.readEof();
}

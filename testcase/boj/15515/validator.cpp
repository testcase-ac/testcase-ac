#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 25, "n");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        string row = inf.readToken("[BW]{1,25}", "row");
        ensuref((int)row.size() == n, "row %d has length %d, expected %d",
                i + 1, (int)row.size(), n);
        inf.readEoln();
    }

    inf.readEof();
}

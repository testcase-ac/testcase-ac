#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 500, "N");
    inf.readSpace();
    int m = inf.readInt(1, 500, "M");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        vector<int> row = inf.readInts(m, 0, 1, "top_cell");
        inf.readEoln();
    }

    inf.readInts(m, 0, 100, "front_height");
    inf.readEoln();

    inf.readInts(n, 0, 100, "right_height");
    inf.readEoln();

    inf.readEof();
}

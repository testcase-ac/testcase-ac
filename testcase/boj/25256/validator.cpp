#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int h = inf.readInt(1, 100000, "h");
    inf.readSpace();
    int w = inf.readInt(1, 100000, "w");
    inf.readEoln();

    ensuref(1LL * h * w <= 100000LL, "h * w must be at most 100000");

    for (int i = 0; i < h; ++i) {
        string row = inf.readToken("[A-Z]{1,100000}", "row");
        ensuref(static_cast<int>(row.size()) == w,
                "row %d length is %d, expected %d", i + 1,
                static_cast<int>(row.size()), w);
        inf.readEoln();
    }

    inf.readEof();
}

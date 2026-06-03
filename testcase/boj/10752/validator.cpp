#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int r = inf.readInt(2, 15, "R");
    inf.readSpace();
    int c = inf.readInt(2, 15, "C");
    inf.readEoln();

    for (int i = 0; i < r; ++i) {
        string row = inf.readToken("[RB]{2,15}", "row");
        ensuref((int)row.size() == c, "row %d has length %d, expected %d", i + 1,
                (int)row.size(), c);
        inf.readEoln();
    }

    inf.readEof();
}

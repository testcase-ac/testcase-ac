#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int R = inf.readInt(1, 500, "R");
    inf.readSpace();
    int C = inf.readInt(1, 500, "C");
    inf.readEoln();

    for (int r = 0; r < R; ++r) {
        string row = inf.readToken("[.SW]{1,500}", "row");
        inf.readEoln();
        ensuref((int)row.size() == C,
                "row %d has length %d, expected %d", r + 1, (int)row.size(), C);
    }

    inf.readEof();
    return 0;
}

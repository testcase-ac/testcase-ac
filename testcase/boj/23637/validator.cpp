#include "testlib.h"

#include <string>

using namespace std;

namespace {

void readPoint(const string& yName, const string& xName) {
    int y = inf.readInt(-1000, 1000, yName);
    inf.readSpace();
    int x = inf.readInt(-1000, 1000, xName);
    inf.readEoln();

    ensuref(y != 0 || x != 0, "object position must not be the origin");
}

}  // namespace

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int q = inf.readInt(1, 100000, "Q");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        readPoint("y_i", "x_i");
    }

    for (int i = 1; i <= q; ++i) {
        int type = inf.readInt(1, 2, "type_i");
        inf.readSpace();

        if (type == 1) {
            readPoint("y_i", "x_i");
            continue;
        }

        string direction = inf.readToken("L|R", "direction_i");
        inf.readSpace();
        inf.readInt(0, 360, "a_i");
        inf.readSpace();
        inf.readInt(0, 360, "b_i");
        inf.readSpace();
        inf.readInt(1, 1000, "r_i");
        inf.readSpace();
        inf.readInt(0, 200000, "c_i");
        inf.readEoln();
    }

    inf.readEof();
}

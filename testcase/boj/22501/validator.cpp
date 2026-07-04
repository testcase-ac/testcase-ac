#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 16, "N");
    inf.readEoln();

    set<pair<int, int>> stamps;
    for (int i = 1; i <= n; ++i) {
        int h = inf.readInt(1, 4, "H_i");
        inf.readSpace();
        int w = inf.readInt(1, 4, "W_i");
        inf.readEoln();

        ensuref(stamps.insert({h, w}).second,
                "duplicate stamp dimensions at index %d: %d %d", i, h, w);
    }

    for (int row = 1; row <= 4; ++row) {
        inf.readToken("[RGB]{4}", "C_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}

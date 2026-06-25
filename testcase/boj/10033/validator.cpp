#include "testlib.h"

#include <set>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "n");
    inf.readEoln();

    set<int> positions;
    bool hasWhite = false;
    for (int i = 0; i < n; ++i) {
        int x = inf.readInt(0, 1000000000, "x_i");
        inf.readSpace();
        string color = inf.readToken("W|S", "color_i");
        inf.readEoln();

        ensuref(positions.insert(x).second,
                "duplicate position at cow %d: %d", i + 1, x);
        hasWhite = hasWhite || color == "W";
    }

    ensuref(hasWhite, "there must be at least one white cow");
    inf.readEof();
}

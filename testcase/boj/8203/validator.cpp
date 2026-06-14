#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 1000000, "m");
    inf.readEoln();

    string lollipop = inf.readToken("[TW]+", "lollipop");
    ensuref(static_cast<int>(lollipop.size()) == n,
            "lollipop length must be n: expected %d, found %d",
            n,
            static_cast<int>(lollipop.size()));
    inf.readEoln();

    for (int i = 0; i < m; ++i) {
        inf.readInt(1, 2000000, "k");
        inf.readEoln();
    }

    inf.readEof();
}

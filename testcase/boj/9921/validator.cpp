#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 20, "N");
    inf.readSpace();
    int v = inf.readInt(1, 150, "V");
    inf.readSpace();
    int w = inf.readInt(1, 150, "W");
    inf.readEoln();

    set<pair<int, int>> denominations;
    for (int i = 0; i < n; ++i) {
        int coinValue = inf.readInt(1, 150, "v_i");
        inf.readSpace();
        int coinWeight = inf.readInt(1, 150, "w_i");
        inf.readEoln();

        ensuref(denominations.insert({coinValue, coinWeight}).second,
                "duplicate denomination pair at index %d: (%d, %d)",
                i + 1, coinValue, coinWeight);
    }

    inf.readEof();
}

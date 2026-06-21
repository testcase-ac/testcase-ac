#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int m = inf.readInt(2, 10000, "M");
    inf.readSpace();
    int k = inf.readInt(1, 1000, "K");
    inf.readEoln();

    set<pair<int, int>> sensors;
    for (int i = 0; i < n; ++i) {
        int x = inf.readInt(1, m - 1, "x");
        inf.readSpace();
        int y = inf.readInt(1, 9999999, "y");
        inf.readEoln();

        ensuref(sensors.insert({x, y}).second,
                "duplicate sensor at index %d: (%d, %d)", i + 1, x, y);
    }

    inf.readEof();
    return 0;
}

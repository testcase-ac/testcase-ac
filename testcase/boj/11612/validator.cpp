#include "testlib.h"

#include <vector>
using namespace std;

struct Gear {
    int x;
    int y;
    int r;
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 1000, "n");
    inf.readEoln();

    vector<Gear> gears;
    gears.reserve(n);
    for (int i = 0; i < n; ++i) {
        int x = inf.readInt(-10000, 10000, "x_i");
        inf.readSpace();
        int y = inf.readInt(-10000, 10000, "y_i");
        inf.readSpace();
        int r = inf.readInt(1, 10000, "r_i");
        inf.readEoln();

        for (int j = 0; j < i; ++j) {
            long long dx = static_cast<long long>(x) - gears[j].x;
            long long dy = static_cast<long long>(y) - gears[j].y;
            long long radius_sum = static_cast<long long>(r) + gears[j].r;
            ensuref(dx * dx + dy * dy >= radius_sum * radius_sum,
                    "gears %d and %d overlap", j + 1, i + 1);
        }

        gears.push_back({x, y, r});
    }

    inf.readEof();
}

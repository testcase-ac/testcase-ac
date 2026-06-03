#include "testlib.h"

#include <set>
#include <vector>

using namespace std;

namespace {

struct Staircase {
    vector<int> x;
    vector<int> y;
};

Staircase readStaircase(int steps, const char* prefix, set<int>& allX, set<int>& allY) {
    Staircase s;
    s.x.reserve(steps);
    s.y.reserve(steps + 1);

    s.y.push_back(inf.readInt(0, 50000, format("%s_y_0", prefix)));
    ensuref(allY.insert(s.y.back()).second, "duplicate represented y-coordinate: %d", s.y.back());

    for (int i = 1; i <= steps; ++i) {
        inf.readSpace();
        s.x.push_back(inf.readInt(0, 50000, format("%s_x_%d", prefix, i)));
        ensuref(allX.insert(s.x.back()).second, "duplicate represented x-coordinate: %d", s.x.back());

        inf.readSpace();
        s.y.push_back(inf.readInt(0, 50000, format("%s_y_%d", prefix, i)));
        ensuref(allY.insert(s.y.back()).second, "duplicate represented y-coordinate: %d", s.y.back());
    }
    inf.readEoln();

    // CHECK: The statement defines the sequence as a staircase from left to right.
    for (int i = 1; i < steps; ++i) {
        ensuref(s.x[i - 1] < s.x[i], "%s x-coordinates must strictly increase", prefix);
    }

    int direction = (s.y[1] > s.y[0]) ? 1 : -1;
    for (int i = 1; i <= steps; ++i) {
        if (direction == 1) {
            ensuref(s.y[i - 1] < s.y[i], "%s y-coordinates must strictly increase", prefix);
        } else {
            ensuref(s.y[i - 1] > s.y[i], "%s y-coordinates must strictly decrease", prefix);
        }
    }

    return s;
}

}  // namespace

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 25000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 25000, "m");
    inf.readEoln();

    set<int> allX;
    set<int> allY;
    readStaircase(n, "L", allX, allY);
    readStaircase(m, "U", allX, allY);

    inf.readEof();
}

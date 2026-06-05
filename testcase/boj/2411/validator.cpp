#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "N");
    inf.readSpace();
    int m = inf.readInt(1, 100, "M");
    inf.readSpace();
    int a = inf.readInt(1, n * m, "A");
    inf.readSpace();
    int b = inf.readInt(0, n * m, "B");
    inf.readEoln();

    ensuref(a + b <= n * m, "too many item and obstacle cells: A+B=%d, N*M=%d", a + b, n * m);

    set<pair<int, int>> occupied;
    for (int i = 0; i < a; ++i) {
        int x = inf.readInt(1, n, "item_x");
        inf.readSpace();
        int y = inf.readInt(1, m, "item_y");
        inf.readEoln();

        // CHECK: positions describe cells on one map, so marked cells must be distinct.
        ensuref(occupied.insert({x, y}).second,
                "duplicate item or occupied cell at item %d: (%d, %d)", i + 1, x, y);
    }

    for (int i = 0; i < b; ++i) {
        int x = inf.readInt(1, n, "obstacle_x");
        inf.readSpace();
        int y = inf.readInt(1, m, "obstacle_y");
        inf.readEoln();

        // CHECK: positions describe cells on one map, so marked cells must be distinct.
        ensuref(occupied.insert({x, y}).second,
                "duplicate obstacle or occupied cell at obstacle %d: (%d, %d)", i + 1, x, y);
        // CHECK: an obstacle on the start or destination contradicts the stated route endpoints.
        ensuref(!(x == 1 && y == 1), "start cell cannot contain an obstacle");
        ensuref(!(x == n && y == m), "end cell cannot contain an obstacle");
    }

    inf.readEof();
}

#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int TESTS = 4;
    for (int tc = 1; tc <= TESTS; tc++) {
        // Read exactly 8 integers: x, y, p, q for first rect, then for second rect
        vector<int> v = inf.readInts(8, 1, 50000, "coord");
        inf.readEoln();

        int x1 = v[0], y1 = v[1], p1 = v[2], q1 = v[3];
        int x2 = v[4], y2 = v[5], p2 = v[6], q2 = v[7];

        ensuref(x1 < p1,
                "Test case %d: first rectangle has x >= p (%d >= %d)", 
                tc, x1, p1);
        ensuref(y1 < q1,
                "Test case %d: first rectangle has y >= q (%d >= %d)", 
                tc, y1, q1);
        ensuref(x2 < p2,
                "Test case %d: second rectangle has x >= p (%d >= %d)", 
                tc, x2, p2);
        ensuref(y2 < q2,
                "Test case %d: second rectangle has y >= q (%d >= %d)", 
                tc, y2, q2);
    }

    inf.readEof();
    return 0;
}

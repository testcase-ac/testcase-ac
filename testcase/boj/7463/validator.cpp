#include "testlib.h"
#include <set>
#include <utility>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read k
    int k = inf.readInt(1, 1000, "k");
    inf.readEoln();

    for (int tc = 0; tc < k; ++tc) {
        set<pair<int, int>> points;
        for (int i = 0; i < 5; ++i) {
            int x = inf.readInt(-1000, 1000, "x");
            inf.readSpace();
            int y = inf.readInt(-1000, 1000, "y");
            if (i < 4) {
                inf.readSpace();
            } else {
                inf.readEoln();
            }
            // Check for distinctness
            ensuref(points.insert({x, y}).second,
                "Point (%d, %d) is duplicated in test case %d", x, y, tc + 1);
        }
    }

    inf.readEof();
}

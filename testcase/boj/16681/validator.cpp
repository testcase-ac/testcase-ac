#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 200000, "M");
    inf.readSpace();
    inf.readInt(1, 100, "D");
    inf.readSpace();
    inf.readInt(1, 100, "E");
    inf.readEoln();

    vector<int> heights = inf.readInts(n, 1, 1000000, "h_i");
    inf.readEoln();
    ensuref(heights.front() == 1, "height of home vertex 1 must be 1, got %d", heights.front());
    ensuref(heights.back() == 1, "height of university vertex N must be 1, got %d", heights.back());

    for (int i = 1; i <= m; ++i) {
        inf.readInt(1, n, "a");
        inf.readSpace();
        inf.readInt(1, n, "b");
        inf.readSpace();
        inf.readInt(1, 100000, "distance");
        inf.readEoln();
    }

    inf.readEof();
}

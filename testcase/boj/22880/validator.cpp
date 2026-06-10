#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 500000, "N");
    inf.readEoln();

    vector<int> heights = inf.readInts(n, 1, n, "h_i");
    inf.readEoln();

    vector<char> seen(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        int h = heights[i];
        ensuref(!seen[h], "duplicate height %d at position %d", h, i + 1);
        seen[h] = 1;
    }

    inf.readEof();
    return 0;
}

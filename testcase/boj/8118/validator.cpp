#include "testlib.h"

#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 49, "n");
    ensuref(n % 2 == 1, "n must be odd, found %d", n);
    inf.readSpace();

    int totalSquares = n * n;
    set<int> removed;
    for (int i = 0; i < 3; ++i) {
        int square = inf.readInt(1, totalSquares, format("removed_%d", i + 1).c_str());
        ensuref(removed.insert(square).second, "removed square %d appears more than once", square);
        if (i + 1 < 3) {
            inf.readSpace();
        }
    }

    inf.readEoln();
    inf.readEof();
}

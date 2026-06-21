#include "testlib.h"

#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "n");
    inf.readSpace();
    int k = inf.readInt(0, n, "k");
    inf.readSpace();
    int r = inf.readInt(2, n, "r");
    inf.readEoln();

    set<int> cameras;
    for (int i = 0; i < k; ++i) {
        int x = inf.readInt(1, n, "camera_i");
        inf.readEoln();
        ensuref(cameras.insert(x).second,
                "duplicate camera location at index %d: %d", i + 1, x);
    }

    inf.readEof();
}

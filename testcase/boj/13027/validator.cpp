#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "n");
    inf.readEoln();

    set<int> xs;
    for (int i = 1; i <= n; ++i) {
        int x = inf.readInt(1, 1000000000, "x_i");
        inf.readSpace();
        inf.readInt(1, 1000000000, "w_i");
        inf.readEoln();

        ensuref(xs.insert(x).second, "duplicate x_i at point %d: %d", i, x);
    }

    inf.readEof();
}

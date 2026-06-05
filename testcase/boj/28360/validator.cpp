#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 50, "N");
    inf.readSpace();
    int m = inf.readInt(0, 100, "M");
    inf.readEoln();

    set<pair<int, int>> hoses;
    for (int i = 1; i <= m; ++i) {
        int v = inf.readInt(1, n, "v");
        inf.readSpace();
        int w = inf.readInt(1, n, "w");
        inf.readEoln();

        ensuref(v < w, "hose %d must go from a smaller bucket to a larger bucket: %d %d", i, v, w);
        ensuref(hoses.insert({v, w}).second, "duplicate hose %d: %d %d", i, v, w);
    }

    inf.readEof();
    return 0;
}

#include "testlib.h"

#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 1000000, "T");
    inf.readSpace();
    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    set<int> ids;
    long long totalTime = 0;
    for (int i = 1; i <= n; ++i) {
        int a = inf.readInt(1, 1000000, "A_i");
        inf.readSpace();
        int b = inf.readInt(1, 1000000, "B_i");
        inf.readSpace();
        inf.readInt(1, 1000000, "C_i");
        inf.readEoln();

        ensuref(ids.insert(a).second, "duplicate process id at index %d: %d", i, a);
        totalTime += b;
    }

    ensuref(t <= totalTime, "T must not exceed total process time: T=%d, sum B_i=%lld", t, totalTime);

    inf.readEof();
}

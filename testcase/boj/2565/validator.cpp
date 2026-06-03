#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "n");
    inf.readEoln();

    set<int> seenA;
    set<int> seenB;
    for (int i = 0; i < n; ++i) {
        int a = inf.readInt(1, 500, "a");
        inf.readSpace();
        int b = inf.readInt(1, 500, "b");
        inf.readEoln();

        ensuref(seenA.insert(a).second,
                "duplicate A-pole position at wire %d: %d", i + 1, a);
        ensuref(seenB.insert(b).second,
                "duplicate B-pole position at wire %d: %d", i + 1, b);
    }

    inf.readEof();
    return 0;
}

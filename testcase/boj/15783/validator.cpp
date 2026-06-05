#include "testlib.h"

#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 100000, "M");
    inf.readEoln();

    set<pair<int, int>> pipes;
    for (int i = 0; i < m; ++i) {
        int a = inf.readInt(0, n - 1, "A");
        inf.readSpace();
        int b = inf.readInt(0, n - 1, "B");
        inf.readEoln();

        // CHECK: The statement forbids duplicate pipes but does not forbid A == B.
        ensuref(pipes.insert({a, b}).second,
                "duplicate pipe at index %d: %d -> %d", i + 1, a, b);
    }

    inf.readEof();
}

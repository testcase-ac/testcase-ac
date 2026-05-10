#include "testlib.h"
#include <set>
#include <tuple>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 1000, "M");
    inf.readEoln();

    // For each keyboard, store the set of times already used
    vector< set<int> > keyboard_times(N + 1); // 1-based indexing

    for (int i = 0; i < M; ++i) {
        int a = inf.readInt(1, N, "a");
        inf.readSpace();
        int b = inf.readInt(0, 1000000, "b");
        inf.readSpace();
        // c must be a single character: [A-Z0-9]
        string c = inf.readToken("[A-Z0-9]", "c");
        inf.readEoln();

        // For each keyboard, each time can only be used once
        ensuref(keyboard_times[a].insert(b).second,
            "Duplicate time %d for keyboard %d at line %d (1-based)", b, a, i+2);
    }

    inf.readEof();
}

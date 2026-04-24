#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of touching finger pairs
    int N = inf.readInt(1, 10, "N");
    inf.readEoln();

    // To detect duplicate pairs (unordered)
    set<pair<int,int>> seen;

    for (int i = 0; i < N; i++) {
        int u = inf.readInt(1, 5, "u");
        inf.readSpace();
        int v = inf.readInt(1, 5, "v");
        inf.readEoln();

        // No self-touching
        ensuref(u != v,
                "Pair %d is a loop: finger %d touched itself", i+1, u);

        // Represent edge as unordered
        int a = min(u, v), b = max(u, v);
        pair<int,int> p = make_pair(a, b);
        ensuref(!seen.count(p),
                "Duplicate pair detected at line %d: (%d, %d)", i+2, u, v);

        seen.insert(p);
    }

    inf.readEof();
    return 0;
}

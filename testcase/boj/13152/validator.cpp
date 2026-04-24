#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of cities
    int n = inf.readInt(1, 500, "n");
    inf.readEoln();

    // Read number of roads
    int m = inf.readInt(0, 2500, "m");
    inf.readEoln();

    // Ensure no duplicate roads and no loops
    set<pair<int,int>> seen;
    for (int i = 0; i < m; i++) {
        int a = inf.readInt(1, n, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, n, "b_i");
        inf.readEoln();

        ensuref(a != b,
                "Loop detected at edge %d: both endpoints are %d", 
                i+1, a);

        int u = min(a, b), v = max(a, b);
        pair<int,int> e = make_pair(u, v);
        ensuref(!seen.count(e),
                "Multiple edges detected between %d and %d at edge %d", 
                u, v, i+1);
        seen.insert(e);
    }

    inf.readEof();
    return 0;
}

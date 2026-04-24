#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of classmates
    int n = inf.readInt(2, 500, "n");
    inf.readEoln();

    // Read number of friend relations
    int m = inf.readInt(1, 10000, "m");
    inf.readEoln();

    set<pair<int,int>> edges;
    for (int i = 0; i < m; i++) {
        // Read a pair of friends
        vector<int> ab = inf.readInts(2, 1, n, "friend");
        inf.readEoln();

        int a = ab[0], b = ab[1];
        // a < b must hold by problem statement
        ensuref(a < b, "Friendship pair %d is invalid: a (%d) must be less than b (%d)", i+1, a, b);

        // No duplicate edges
        pair<int,int> p = make_pair(a, b);
        ensuref(!edges.count(p), "Duplicate friendship detected at entry %d: (%d, %d)", i+1, a, b);
        edges.insert(p);
    }

    inf.readEof();
    return 0;
}

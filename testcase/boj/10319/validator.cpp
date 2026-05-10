#include "testlib.h"
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read number of test cases
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 0; tc < T; ++tc) {
        setTestCase(tc + 1);

        // 2. Read n
        int n = inf.readInt(1, 1000, "n");
        inf.readEoln();

        // 3. Read i, g, s
        int i = inf.readInt(1, n, "i");
        inf.readSpace();
        int g = inf.readInt(1, 100, "g");
        inf.readSpace();
        int s = inf.readInt(1, 100, "s");
        inf.readEoln();

        // 4. Read m
        int m = inf.readInt(1, n, "m");
        inf.readEoln();

        // 5. Read m hospital locations
        vector<int> hospital(m);
        set<int> hospital_set;
        for (int j = 0; j < m; ++j) {
            hospital[j] = inf.readInt(1, n, "hospital_x");
            inf.readEoln();
            ensuref(hospital_set.insert(hospital[j]).second, 
                "Duplicate hospital location at index %d: %d", j, hospital[j]);
        }

        // 6. Read r
        int r = inf.readInt(0, 1000, "r");
        inf.readEoln();

        // 7. Read r roads
        // For each pair (a,b), at most one edge from a to b, and a != b
        set<pair<int, int>> edge_set;
        for (int j = 0; j < r; ++j) {
            int a = inf.readInt(1, n, "a");
            inf.readSpace();
            int b = inf.readInt(1, n, "b");
            inf.readSpace();
            int p = inf.readInt(1, 100, "p");
            inf.readSpace();
            int t = inf.readInt(1, 100, "t");
            inf.readEoln();

            ensuref(a != b, "Self-loop detected at road index %d: (%d, %d)", j, a, b);
            ensuref(edge_set.insert({a, b}).second, 
                "Multiple roads in same direction detected at road index %d: (%d, %d)", j, a, b);
        }
    }

    inf.readEof();
}

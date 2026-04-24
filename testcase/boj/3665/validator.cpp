#include "testlib.h"
#include <vector>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int tc = inf.readInt(1, 100, "tc");
    inf.readEoln();

    for (int tcnum = 1; tcnum <= tc; tcnum++) {
        setTestCase(tcnum);

        // Number of teams
        int n = inf.readInt(2, 500, "n");
        inf.readEoln();

        // Last year's ranking: a permutation of [1..n]
        vector<int> t = inf.readInts(n, 1, n, "t_i");
        inf.readEoln();
        {
            vector<char> seen(n+1, 0);
            for (int i = 0; i < n; i++) {
                int team = t[i];
                ensuref(!seen[team],
                        "Duplicate team %d in t_i at position %d", 
                        team, i+1);
                seen[team] = 1;
            }
        }

        // Number of changed pairs
        int m = inf.readInt(0, 25000, "m");
        inf.readEoln();

        // Read each changed pair (a_i, b_i), with 1 <= a_i < b_i <= n, no duplicates
        set<pair<int,int>> changed;
        for (int i = 1; i <= m; i++) {
            int a = inf.readInt(1, n, "a_i");
            inf.readSpace();
            int b = inf.readInt(1, n, "b_i");
            inf.readEoln();

            ensuref(a < b,
                    "Changed pair a_i >= b_i at index %d: (%d, %d)", 
                    i, a, b);

            pair<int,int> pr = make_pair(a, b);
            ensuref(!changed.count(pr),
                    "Duplicate changed pair at index %d: (%d, %d)", 
                    i, a, b);
            changed.insert(pr);
        }
    }

    inf.readEof();
    return 0;
}

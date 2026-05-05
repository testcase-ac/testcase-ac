#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
#include <queue>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAX_N = 100;
    const int MIN_TIME = 1;
    const int MAX_TIME = 10;
    const int MAX_CASES = 100000;

    int case_cnt = 0;
    while (true) {
        // Read number of stockbrokers
        int n = inf.readInt(0, MAX_N, "n");
        inf.readEoln();

        if (n == 0) {
            break;
        }

        ++case_cnt;
        ensuref(case_cnt <= MAX_CASES, "Too many test cases: %d (maximum allowed is %d)", case_cnt, MAX_CASES);

        // For each stockbroker, read their contacts
        vector< set<int> > contacts(n); // for checking duplicate contacts
        vector< vector< pair<int,int> > > adj(n); // adjacency list: (to, time)
        for (int i = 0; i < n; ++i) {
            int m = inf.readInt(0, n-1, "contact_count");
            vector<int> tokens;
            if (m > 0) {
                for (int j = 0; j < m; ++j) {
                    inf.readSpace();
                    int to = inf.readInt(1, n, "contact_id");
                    inf.readSpace();
                    int t = inf.readInt(MIN_TIME, MAX_TIME, "contact_time");
                    // Check for duplicate contacts
                    ensuref(!contacts[i].count(to-1), "Duplicate contact from person %d to %d", i+1, to);
                    ensuref(to-1 != i, "Self contact detected for person %d", i+1);
                    contacts[i].insert(to-1);
                    adj[i].emplace_back(to-1, t);
                }
            }
            inf.readEoln();
        }

        // No further global property is required to be validated from validator's perspective.
        // The problem says: "It is possible that your program will receive a network of connections that excludes some persons, i.e. some people may be unreachable."
        // So, disconnected graphs are allowed.

        // However, we should check that the input is not malformed: e.g. no duplicate contacts, no self-loops, contact ids in range, times in range.
        // Already checked above.

        // No further checks needed.
    }

    inf.readEof();
}

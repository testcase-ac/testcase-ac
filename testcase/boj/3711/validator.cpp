#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAX_ID = 1000000 - 1;

    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 0; tc < T; ++tc) {
        setTestCase(tc + 1);

        int G = inf.readInt(1, 300, "G");
        inf.readEoln();

        vector<int> ids;
        ids.reserve(G);
        for (int i = 0; i < G; ++i) {
            int x = inf.readInt(0, MAX_ID, "student_id");
            inf.readEoln();
            ids.push_back(x);
        }

        // Check IDs are distinct
        {
            vector<int> tmp = ids;
            sort(tmp.begin(), tmp.end());
            for (int i = 1; i < G; ++i) {
                ensuref(tmp[i] != tmp[i - 1],
                        "student IDs must be distinct, but value %d appears at least twice "
                        "(e.g., positions %d and %d in this test case)",
                        tmp[i], i, i + 1);
            }
        }

        // Optional global property: the answer always exists.
        // We verify by computing the minimal m such that all ids are distinct modulo m.
        // This is to ensure no invalid tests contradict the problem guarantee.
        int maxId = 0;
        for (int x : ids) maxId = max(maxId, x);

        // Upper bound for m: maxId + 1 works because all ids lie in [0, maxId]
        int bestM = 0;
        for (int m = 1; m <= maxId + 1; ++m) {
            // check all remainders distinct modulo m
            // m <= maxId+1 <= 1e6 => G <= 300, so using vector<char> is fine
            vector<int> seen(m, -1);
            bool ok = true;
            for (int i = 0; i < G && ok; ++i) {
                int r = ids[i] % m;
                if (seen[r] != -1) {
                    ok = false;
                } else {
                    seen[r] = i;
                }
            }
            if (ok) {
                bestM = m;
                break;
            }
        }
        ensuref(bestM != 0,
                "no valid m found up to maxId+1=%d for this test case, "
                "contradicting the problem guarantee", maxId + 1);
    }

    inf.readEof();
}

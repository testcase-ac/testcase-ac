#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of queries
    int M = inf.readInt(1, 500000, "M");
    inf.readEoln();

    // We will maintain a multiset-like structure (count map) and simulate
    // the operations to check global guarantees:
    //
    // - Queries of type 2: "항상 A에 x가 있는 쿼리만 주어진다."
    //   We must ensure x is present when such a query is read.
    //
    // - Also we track that there is at least one type 3 or 4 query,
    //   though this is also guaranteed; we still verify.

    unordered_map<long long, long long> cnt;
    cnt.reserve(1 << 18);
    cnt.max_load_factor(0.7);

    // Initial array A has a single 0.
    cnt[0] = 1;
    long long sizeA = 1;

    bool hasOutputQuery = false;

    for (int i = 0; i < M; ++i) {
        int type = inf.readInt(1, 4, "type");
        if (type == 1 || type == 2) {
            inf.readSpace();
            long long x = inf.readLong(1LL, 1000000000LL, "x");
            inf.readEoln();

            if (type == 1) {
                // append x
                cnt[x]++;
                sizeA++;
            } else {
                // remove x, must exist
                auto it = cnt.find(x);
                ensuref(it != cnt.end() && it->second > 0,
                        "Query %d: remove of non-existent value %lld", i + 1, x);
                it->second--;
                sizeA--;
                // We also know initial 0 exists; sizeA can go down to 0 only
                // if we removed that 0 via some query 2 0, but 0 is not allowed,
                // since x is in [1, 1e9], so sizeA should remain >= 1.
                ensuref(sizeA >= 1,
                        "Query %d: array A became empty, but 0 can never be removed", i + 1);
            }
        } else {
            // type 3 or 4 without argument
            inf.readEoln();
            hasOutputQuery = true;
            // No further semantic constraints to validate for 3/4
        }
    }

    ensuref(hasOutputQuery, "There must be at least one query of type 3 or 4");

    inf.readEof();
}

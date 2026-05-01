#include "testlib.h"
using namespace std;

struct Query {
    int type;
    long long x;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int baseM = rnd.next(5, 35); // base number of queries
    vector<Query> queries;
    queries.reserve(baseM + 2);

    vector<long long> pool;       // current elements (positive only)
    vector<long long> usedValues; // values that have appeared in adds
    bool hasOutput = false;       // at least one type 3 or 4

    int valMode = rnd.next(0, 3); // 0: small, 1: powers of two, 2: large, 3: mixed (handled in lambda)

    auto genValue = [&](int mode) -> long long {
        if (mode == 0) {
            // small numbers 1..10
            return rnd.next(1, 10);
        } else if (mode == 1) {
            // powers of two up to 2^9 = 512
            int e = rnd.next(0, 9);
            return 1LL << e;
        } else if (mode == 2) {
            // full range
            return rnd.next(1, 1000000000);
        } else { // mixed
            int t = rnd.next(0, 2);
            if (t == 0) return rnd.next(1, 10);
            if (t == 1) {
                int e = rnd.next(0, 9);
                return 1LL << e;
            }
            return rnd.next(1, 1000000000);
        }
    };

    for (int i = 0; i < baseM; i++) {
        bool hasPositives = !pool.empty();

        int type;
        int r = rnd.next(0, 99);
        if (!hasPositives) {
            // cannot remove if no positive elements
            if (r < 60) type = 1;           // add
            else if (r < 80) type = 3;      // sum
            else type = 4;                  // xor
        } else {
            // 1,2,3,4 all possible
            if (r < 40) type = 1;           // add
            else if (r < 65) type = 2;      // remove
            else if (r < 85) type = 3;      // sum
            else type = 4;                  // xor
        }

        if (type == 1) {
            long long x;
            if (!usedValues.empty() && rnd.next(0, 99) < 40) {
                // reuse an existing value to create duplicates
                x = rnd.any(usedValues);
            } else {
                x = genValue(valMode == 3 ? 3 : valMode);
            }
            pool.push_back(x);
            usedValues.push_back(x);
            queries.push_back({1, x});
        } else if (type == 2) {
            // remove one existing positive value
            int idx = rnd.next((int)pool.size());
            long long x = pool[idx];
            pool[idx] = pool.back();
            pool.pop_back();
            queries.push_back({2, x});
        } else if (type == 3) {
            queries.push_back({3, 0});
            hasOutput = true;
        } else { // type == 4
            queries.push_back({4, 0});
            hasOutput = true;
        }
    }

    // Ensure at least one output query (type 3 or 4)
    if (!hasOutput) {
        int t = rnd.next(3, 4);
        queries.push_back({t, 0});
    }

    println((int)queries.size());
    for (auto &q : queries) {
        if (q.type == 1 || q.type == 2)
            println(q.type, q.x);
        else
            println(q.type);
    }

    return 0;
}

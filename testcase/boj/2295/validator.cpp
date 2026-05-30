#include "testlib.h"
#include <algorithm>
#include <unordered_set>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(5, 1000, "N");
    inf.readEoln();

    vector<int> values;
    unordered_set<int> seen;
    for (int i = 0; i < n; ++i) {
        int x = inf.readInt(1, 200000000, "U_i");
        inf.readEoln();
        ensuref(!seen.count(x), "duplicate element at index %d: %d", i + 1, x);
        seen.insert(x);
        values.push_back(x);
    }

    unordered_set<long long> pairSums;
    pairSums.reserve(static_cast<size_t>(n) * n * 2);
    for (int a : values) {
        for (int b : values) {
            pairSums.insert(1LL * a + b);
        }
    }

    bool found = false;
    for (int d : values) {
        for (int c : values) {
            if (pairSums.count(1LL * d - c)) {
                found = true;
                break;
            }
        }
        if (found) {
            break;
        }
    }
    ensuref(found, "no answer exists: no U[x] + U[y] + U[z] equals an element of U");

    inf.readEof();
}

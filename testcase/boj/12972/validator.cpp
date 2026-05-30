#include "testlib.h"
#include <algorithm>
#include <map>
#include <numeric>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 500, "N");
    inf.readEoln();

    int total = n * n;
    vector<int> values = inf.readInts(total, 1, 1000000000, "g_ij");
    inf.readEoln();

    vector<int> sorted = values;
    sort(sorted.rbegin(), sorted.rend());

    map<int, int, greater<int>> remaining;
    for (int value : sorted) {
        ++remaining[value];
    }

    vector<int> restored;
    restored.reserve(n);
    for (int value : sorted) {
        auto self = remaining.find(value);
        if (self == remaining.end() || self->second == 0) {
            continue;
        }

        --self->second;

        for (int previous : restored) {
            int g = gcd(value, previous);
            auto it = remaining.find(g);
            ensuref(it != remaining.end() && it->second >= 2,
                    "GCD table cannot be restored: missing pair gcd %d for %d and %d",
                    g, value, previous);
            it->second -= 2;
        }

        restored.push_back(value);
    }

    ensuref((int)restored.size() == n,
            "GCD table cannot be restored: expected %d source values, got %d",
            n, (int)restored.size());

    for (const auto& [value, count] : remaining) {
        ensuref(count == 0,
                "GCD table cannot be restored: leftover value %d appears %d times",
                value, count);
    }

    inf.readEof();
}

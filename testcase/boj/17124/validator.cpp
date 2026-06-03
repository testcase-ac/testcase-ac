#include "testlib.h"

#include <unordered_set>
#include <vector>

using namespace std;

namespace {
constexpr int MAX_T = 10;
constexpr int MAX_NM = 1000000;
constexpr int MAX_VALUE = 1000000000;

void ensureDistinct(const vector<int>& values, const char* name) {
    unordered_set<int> seen;
    seen.reserve(values.size() * 2);
    for (int i = 0; i < (int)values.size(); ++i) {
        ensuref(seen.insert(values[i]).second,
                "duplicate %s value at index %d: %d",
                name, i + 1, values[i]);
    }
}
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, MAX_T, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, MAX_NM, "n");
        inf.readSpace();
        int m = inf.readInt(1, MAX_NM, "m");
        inf.readEoln();

        vector<int> a = inf.readInts(n, 1, MAX_VALUE, "A_i");
        inf.readEoln();
        ensureDistinct(a, "A");

        vector<int> b = inf.readInts(m, 1, MAX_VALUE, "B_i");
        inf.readEoln();
        ensureDistinct(b, "B");
    }

    inf.readEof();
    return 0;
}

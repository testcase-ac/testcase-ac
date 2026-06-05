#include "testlib.h"

#include <string>
#include <unordered_set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 5000000, "N");
    inf.readEoln();

    unordered_set<string> destinations;
    destinations.reserve(static_cast<size_t>(n) * 2);

    bool hasJinju = false;
    for (int i = 1; i <= n; ++i) {
        string d = inf.readToken("[a-z]{1,15}", "D_i");
        inf.readSpace();
        long long c = inf.readLong(1LL, 1000000000000000LL, "C_i");
        inf.readEoln();

        ensuref(destinations.insert(d).second,
                "duplicate destination at row %d: %s", i, d.c_str());
        if (d == "jinju") {
            ensuref(!hasJinju, "multiple jinju destinations");
            ensuref(c <= 1000LL, "jinju cost must be at most 1000, found %lld", c);
            hasJinju = true;
        }
    }

    ensuref(hasJinju, "missing jinju destination");
    inf.readEof();
}

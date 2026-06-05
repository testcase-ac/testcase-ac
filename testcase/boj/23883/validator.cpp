#include "testlib.h"

#include <unordered_set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(5, 500000, "n");
    inf.readSpace();
    int k = inf.readInt(1, n, "k");
    inf.readEoln();

    unordered_set<int> seen;
    seen.reserve(static_cast<size_t>(n) * 2);
    for (int i = 1; i <= n; ++i) {
        if (i > 1) {
            inf.readSpace();
        }
        int value = inf.readInt(1, 1000000000, "a_i");
        ensuref(seen.insert(value).second, "duplicate a_i at index %d: %d", i, value);
    }
    inf.readEoln();
    inf.readEof();
}

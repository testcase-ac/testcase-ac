#include "testlib.h"

#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(5, 10000, "N");
    inf.readSpace();
    long long k = inf.readLong(1LL, 1LL * n * n, "K");
    inf.readEoln();

    set<int> seen;
    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        int value = inf.readInt(1, 1000000000, "A_i");
        ensuref(seen.insert(value).second, "duplicate A_i at index %d: %d", i + 1, value);
    }
    inf.readEoln();
    inf.readEof();
}

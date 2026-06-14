#include "testlib.h"

#include <unordered_set>
#include <vector>

using namespace std;

bool isPrime(int x) {
    if (x < 2) {
        return false;
    }
    if (x % 2 == 0) {
        return x == 2;
    }
    for (int d = 3; 1LL * d * d <= x; d += 2) {
        if (x % d == 0) {
            return false;
        }
    }
    return true;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "N");
    inf.readSpace();
    int p = inf.readInt(2, 1000000000, "P");
    inf.readSpace();
    int k = inf.readInt(0, p - 1, "K");
    inf.readEoln();

    ensuref(isPrime(p), "P must be prime: %d", p);

    vector<int> a = inf.readInts(n, 0, p - 1, "A_i");
    inf.readEoln();

    unordered_set<int> seen;
    seen.reserve(static_cast<size_t>(n) * 2);
    for (int i = 0; i < n; ++i) {
        ensuref(seen.insert(a[i]).second,
                "duplicate A_i at index %d: %d",
                i + 1,
                a[i]);
    }

    inf.readEof();
}

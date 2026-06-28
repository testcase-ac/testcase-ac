#include "testlib.h"

#include <unordered_set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    long long n = inf.readLong(1LL, 1000000000LL, "N");
    inf.readSpace();
    long long l = inf.readLong(1LL, n, "l");
    inf.readSpace();
    int q = inf.readInt(1, 100000, "Q");
    inf.readEoln();

    ensuref(n % l == 0, "N must be divisible by l: N=%lld, l=%lld", n, l);

    unordered_set<long long> topped;
    topped.reserve(static_cast<size_t>(q) * 2 + 1);

    for (int i = 1; i <= q; ++i) {
        int type = inf.readInt(1, 2, "query_type");
        inf.readSpace();
        long long x = inf.readLong(1LL, n, "x");

        if (type == 1) {
            inf.readSpace();
            inf.readLong(1LL, 1000000000LL, "t");
            topped.insert(x);
        } else {
            ensuref(topped.erase(x) == 1,
                    "remove query %d targets a slice without topping: x=%lld", i, x);
        }

        inf.readEoln();
    }

    inf.readEof();
}

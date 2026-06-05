#include "testlib.h"

#include <numeric>
#include <set>
#include <tuple>

using namespace std;

tuple<long long, long long, long long> normalizeLine(long long a, long long b, long long c) {
    long long g = gcd(gcd(llabs(a), llabs(b)), llabs(c));
    a /= g;
    b /= g;
    c /= g;

    if (a < 0 || (a == 0 && b < 0) || (a == 0 && b == 0 && c < 0)) {
        a = -a;
        b = -b;
        c = -c;
    }

    return {a, b, c};
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 500000, "N");
    inf.readEoln();

    set<tuple<long long, long long, long long>> lines;
    for (int i = 1; i <= n; ++i) {
        long long a = inf.readLong(-1000000000LL, 1000000000LL, "a_i");
        inf.readSpace();
        long long b = inf.readLong(-1000000000LL, 1000000000LL, "b_i");
        inf.readSpace();
        long long c = inf.readLong(-1000000000LL, 1000000000LL, "c_i");
        inf.readEoln();

        ensuref(a != 0 || b != 0, "(a_i, b_i) is (0, 0) at line %d", i);

        auto normalized = normalizeLine(a, b, c);
        ensuref(lines.insert(normalized).second, "duplicate geometric line at index %d", i);
    }

    inf.readEof();
}

#include "testlib.h"
#include <set>
#include <tuple>
using namespace std;
using ll = long long;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readEoln();

    set<tuple<ll, ll, ll>> coords;
    for (int i = 0; i < n; i++) {
        ll x = inf.readLong(-1000000000LL, 1000000000LL, "x_i");
        inf.readSpace();
        ll y = inf.readLong(-1000000000LL, 1000000000LL, "y_i");
        inf.readSpace();
        ll z = inf.readLong(-1000000000LL, 1000000000LL, "z_i");
        inf.readEoln();

        auto t = make_tuple(x, y, z);
        ensuref(!coords.count(t),
                "Duplicate coordinate at planet %d: (%lld, %lld, %lld)",
                i + 1, x, y, z);
        coords.insert(t);
    }

    inf.readEof();
    return 0;
}

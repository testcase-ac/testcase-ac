#include "testlib.h"
#include <set>
using namespace std;
using ll = long long;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read grid dimensions
    ll W = inf.readLong(1LL, 1000000000LL, "W");
    inf.readSpace();
    ll H = inf.readLong(1LL, 1000000000LL, "H");
    inf.readEoln();

    // Read number of houses
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // Read house coordinates and check uniqueness
    set<pair<ll,ll>> seen;
    for (int i = 0; i < N; i++) {
        ll x = inf.readLong(1LL, W, "x_i");
        inf.readSpace();
        ll y = inf.readLong(1LL, H, "y_i");
        inf.readEoln();
        ensuref(!seen.count({x, y}),
                "Duplicate house detected at index %d: (%lld, %lld)", i+1, x, y);
        seen.insert({x, y});
    }

    inf.readEof();
    return 0;
}

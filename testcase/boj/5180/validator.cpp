#include "testlib.h"

#include <cmath>
#include <set>
#include <string>
#include <utility>

using namespace std;

namespace {

long double readNonnegativeReal(const string& name) {
    string token = inf.readToken("[0-9]{1,20}|[0-9]{1,20}[.][0-9]{1,20}", name);
    size_t dot = token.find('.');
    string integerPart = dot == string::npos ? token : token.substr(0, dot);

    ensuref(integerPart == "0" || integerPart[0] != '0',
            "%s has a leading zero: %s", name.c_str(), token.c_str());
    return stold(token);
}

}  // namespace

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement gives no K limit; this local cap prevents unbounded input size.
    int k = inf.readInt(1, 100000, "K");
    inf.readEoln();

    const long double twoPi = 2.0L * acosl(-1.0L);

    for (int tc = 1; tc <= k; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 200, "N");
        inf.readEoln();

        set<pair<long double, long double>> points;
        for (int i = 1; i <= n; ++i) {
            long double alpha = readNonnegativeReal("alpha");
            inf.readSpace();
            long double radius = readNonnegativeReal("r");
            inf.readEoln();

            ensuref(alpha >= 0.0L && alpha < twoPi,
                    "alpha at nugget %d must satisfy 0 <= alpha < 2*pi", i);
            ensuref(radius > 0.0L && radius <= 1.0L,
                    "r at nugget %d must satisfy 0 < r <= 1", i);
            ensuref(points.insert({alpha, radius}).second,
                    "duplicate nugget position at index %d", i);
        }
    }

    inf.readEof();
}

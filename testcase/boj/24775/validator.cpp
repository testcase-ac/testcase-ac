#include "testlib.h"

#include <string>

using namespace std;

namespace {

long double readDecimal(const string& name, long double low, long double high,
                        bool lowInclusive, bool highInclusive) {
    string token = inf.readToken("[0-9]{1,3}|[0-9]{1,3}\\.[0-9]+", name.c_str());

    size_t dot = token.find('.');
    string whole = dot == string::npos ? token : token.substr(0, dot);
    ensuref(whole == "0" || whole[0] != '0', "%s has a leading zero: %s",
            name.c_str(), token.c_str());

    long double value = stold(token);
    ensuref(lowInclusive ? value >= low : value > low,
            "%s is below the lower bound: %s", name.c_str(), token.c_str());
    ensuref(highInclusive ? value <= high : value < high,
            "%s is above the upper bound: %s", name.c_str(), token.c_str());

    return value;
}

}  // namespace

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "N");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        setTestCase(i);

        readDecimal("v0", 0.0L, 200.0L, false, true);
        inf.readSpace();
        readDecimal("theta", 0.0L, 90.0L, false, false);
        inf.readSpace();
        readDecimal("x1", 0.0L, 1000.0L, false, false);
        inf.readSpace();
        long double h1 = readDecimal("h1", 0.0L, 1000.0L, false, false);
        inf.readSpace();
        long double h2 = readDecimal("h2", 0.0L, 1000.0L, false, false);
        ensuref(h1 < h2, "h1 must be less than h2: h1=%Lf h2=%Lf", h1, h2);
        inf.readEoln();
    }

    inf.readEof();
}

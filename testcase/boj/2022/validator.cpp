#include "testlib.h"
#include <string>
#include <cstdlib>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Real number: either integer [0-9]+ or [0-9]+.[0-9]{1,6}
    // Using alternation since grouping may be unsupported
    const string realRegex = "[0-9]+[.][0-9]{1,6}|[0-9]+";

    // Read x, y, c
    string sx = inf.readToken(realRegex, "x");
    inf.readSpace();
    string sy = inf.readToken(realRegex, "y");
    inf.readSpace();
    string sc = inf.readToken(realRegex, "c");
    inf.readEoln();

    // Convert to long double
    long double x = stold(sx);
    long double y = stold(sy);
    long double c = stold(sc);

    // Constants
    const long double MAXV = 3000000000.0L;
    const long double EPS = 1e-9L;

    // Bounds checks
    ensuref(x > 0.0L, "x must be positive, found %Lf", x);
    ensuref(y > 0.0L, "y must be positive, found %Lf", y);
    ensuref(c > 0.0L, "c must be positive, found %Lf", c);
    ensuref(x <= MAXV + EPS, "x must be <= 3e9, found %Lf", x);
    ensuref(y <= MAXV + EPS, "y must be <= 3e9, found %Lf", y);
    ensuref(c <= MAXV + EPS, "c must be <= 3e9, found %Lf", c);

    // Geometry requirement: crossing height must be strictly less than both ladder lengths
    ensuref(c < x, "c must be strictly less than x: c=%Lf, x=%Lf", c, x);
    ensuref(c < y, "c must be strictly less than y: c=%Lf, y=%Lf", c, y);

    inf.readEof();
    return 0;
}

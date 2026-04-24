#include "testlib.h"
#include <string>
#include <cstdlib>
#include <cerrno>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read A: must be a decimal with exactly two digits after the dot
    string sA = inf.readToken("[0-9]+\\.[0-9]{2}", "A");
    inf.readSpace();
    // Read B: same format
    string sB = inf.readToken("[0-9]+\\.[0-9]{2}", "B");
    inf.readEoln();

    // Parse and check numerical ranges: 0 < A, B <= 1e8
    // Use strtod for robust conversion and overflow detection
    char* endptr = nullptr;
    errno = 0;
    double A = strtod(sA.c_str(), &endptr);
    ensuref(endptr != sA.c_str() && *endptr == '\0' && errno == 0,
            "Failed to parse A as double: '%s'", sA.c_str());
    ensuref(A > 0.0, "A must be > 0, but got %s", sA.c_str());
    ensuref(A <= 1e8, "A must be <= 1e8, but got %s", sA.c_str());

    errno = 0;
    double B = strtod(sB.c_str(), &endptr);
    ensuref(endptr != sB.c_str() && *endptr == '\0' && errno == 0,
            "Failed to parse B as double: '%s'", sB.c_str());
    ensuref(B > 0.0, "B must be > 0, but got %s", sB.c_str());
    ensuref(B <= 1e8, "B must be <= 1e8, but got %s", sB.c_str());

    inf.readEof();
    return 0;
}

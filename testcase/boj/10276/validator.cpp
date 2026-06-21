#include "testlib.h"

#include <cerrno>
#include <cmath>
#include <cstdlib>
#include <string>

using namespace std;

double readCoordinate(int limit, const string& name) {
    string token = inf.readToken("0\\.[0-9]+|[1-9][0-9]?\\.[0-9]+", name);

    char* end = nullptr;
    errno = 0;
    double value = strtod(token.c_str(), &end);
    ensuref(errno == 0 && end != nullptr && *end == '\0',
            "%s is not a valid real number: %s", name.c_str(), token.c_str());
    ensuref(0.0 < value && value < limit,
            "%s must satisfy 0 < value < %d, got %s",
            name.c_str(), limit, token.c_str());
    ensuref(floor(value) != value,
            "%s must be non-integer, got %s", name.c_str(), token.c_str());

    return value;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int r = inf.readInt(1, 10, "R");
    inf.readEoln();

    for (int tc = 1; tc <= r; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 100, "N");
        inf.readSpace();
        int m = inf.readInt(1, 100, "M");
        inf.readSpace();
        int k = inf.readInt(1, 10000, "K");
        inf.readEoln();

        for (int i = 1; i <= k; ++i) {
            readCoordinate(n, "x");
            inf.readSpace();
            readCoordinate(m, "y");
            inf.readEoln();
        }
    }

    inf.readEof();
}

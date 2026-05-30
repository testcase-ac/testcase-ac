#include "testlib.h"

#include <cstdlib>
#include <cctype>
#include <string>

using namespace std;

static bool hasValidTenthsFormat(const string& token) {
    int dotCount = 0;
    int digitsAfterDot = 0;
    bool seenDot = false;

    if (token.empty()) {
        return false;
    }
    for (char ch : token) {
        if (ch == '.') {
            ++dotCount;
            seenDot = true;
        } else if (isdigit(static_cast<unsigned char>(ch))) {
            if (seenDot) {
                ++digitsAfterDot;
            }
        } else {
            return false;
        }
    }

    return dotCount <= 1 && (!seenDot || digitsAfterDot == 1) && token.front() != '.' &&
           token.back() != '.';
}

static double readBoundedTenths(const string& name) {
    string token = inf.readToken("[0-9.]+", name);
    ensuref(hasValidTenthsFormat(token), "%s must be a positive real with at most one decimal digit, found %s",
            name.c_str(), token.c_str());
    double value = strtod(token.c_str(), nullptr);
    ensuref(0.0 < value && value <= 1000.0, "%s must be in (0, 1000.0], found %s",
            name.c_str(), token.c_str());
    return value;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 30, "N");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        readBoundedTenths("x");
        inf.readSpace();
        readBoundedTenths("y");
        inf.readSpace();
        readBoundedTenths("width");
        inf.readSpace();
        readBoundedTenths("height");
        inf.readEoln();
    }

    inf.readEof();
}

#include "testlib.h"

#include <string>

using namespace std;

namespace {

bool isCanonicalDecimal(const string& value) {
    if (value.empty()) {
        return false;
    }
    if (value.size() > 1 && value[0] == '0') {
        return false;
    }
    for (char ch : value) {
        if (ch < '0' || ch > '9') {
            return false;
        }
    }
    return true;
}

bool lessOrEqualDecimal(const string& value, const string& upperBound) {
    if (value.size() != upperBound.size()) {
        return value.size() < upperBound.size();
    }
    return value <= upperBound;
}

string readBoundedDecimal(const char* name, const string& upperBound) {
    string value = inf.readToken("[0-9]{1,21}", name);
    ensuref(isCanonicalDecimal(value), "%s must be a canonical nonnegative decimal integer", name);
    ensuref(lessOrEqualDecimal(value, upperBound), "%s exceeds upper bound %s", name,
            upperBound.c_str());
    return value;
}

} // namespace

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    readBoundedDecimal("a", "100000000000000000000");
    inf.readSpace();
    readBoundedDecimal("b", "100000000000000000000");
    inf.readSpace();
    readBoundedDecimal("r", "9223372036854775807");
    inf.readEoln();
    inf.readEof();
}

#include "testlib.h"

#include <string>
using namespace std;

namespace {

const long long kMaxValue = 1000000000000000000LL;

bool hasNine(long long value) {
    string s = to_string(value);
    return s.find('9') != string::npos;
}

void validateLegalNumber(long long value, const char* name) {
    ensuref(!hasNine(value), "%s contains digit 9: %lld", name, value);
    ensuref(value % 9 != 0, "%s is divisible by 9: %lld", name, value);
}

}  // namespace

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int caseIndex = 1; caseIndex <= t; ++caseIndex) {
        setTestCase(caseIndex);

        long long f = inf.readLong(1LL, kMaxValue, "F");
        inf.readSpace();
        long long l = inf.readLong(1LL, kMaxValue, "L");
        inf.readEoln();

        ensuref(f < l, "F must be less than L: F=%lld, L=%lld", f, l);
        validateLegalNumber(f, "F");
        validateLegalNumber(l, "L");
    }

    inf.readEof();
}

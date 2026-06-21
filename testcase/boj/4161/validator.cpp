#include "testlib.h"

#include <cstdlib>
#include <string>

using namespace std;

namespace {
const long long kMinCoord = -1000000000LL;
const long long kMaxCoord = 1000000000LL;
const int kMaxCases = 100000;

long long readCoordinateToken(const string& token, const char* name) {
    ensuref(!token.empty(), "%s is empty", name);

    int pos = 0;
    if (token[0] == '-') {
        ensuref(token.size() > 1, "%s has only a minus sign", name);
        pos = 1;
    }

    ensuref(pos + 1 == static_cast<int>(token.size()) || token[pos] != '0',
            "%s has a leading zero: %s", name, token.c_str());
    ensuref(token != "-0", "%s has non-canonical zero: %s", name, token.c_str());

    long long value = strtoll(token.c_str(), nullptr, 10);
    ensuref(kMinCoord <= value && value <= kMaxCoord,
            "%s is out of range: %lld", name, value);
    return value;
}
}  // namespace

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int cases = 0;
    while (true) {
        string first = inf.readToken("END|-?[0-9]{1,10}", "x_or_END");
        if (first == "END") {
            inf.readEoln();
            break;
        }

        ++cases;
        // CHECK: The statement gives no maximum number of coordinate lines.
        ensuref(cases <= kMaxCases, "too many test cases: %d", cases);
        readCoordinateToken(first, "x");

        inf.readSpace();
        string second = inf.readToken("-?[0-9]{1,10}", "y");
        readCoordinateToken(second, "y");
        inf.readEoln();
    }

    inf.readEof();
}

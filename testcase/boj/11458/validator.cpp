#include "testlib.h"

#include <string>

using namespace std;

const int MAX_EXPONENT = 100000;
const int MAX_CASES = 100000; // CHECK: statement gives no case count limit; use local multi-case cap.

bool isCanonicalInteger(const string& s) {
    if (s.empty()) return false;

    int start = 0;
    if (s[0] == '-') {
        if (s.size() == 1) return false;
        if (s[1] == '0') return false;
        start = 1;
    }

    if (s[start] == '0') return s.size() == static_cast<size_t>(start + 1);
    for (int i = start; i < static_cast<int>(s.size()); ++i) {
        if (s[i] < '0' || s[i] > '9') return false;
    }
    return true;
}

bool withinMagnitudeBound(const string& s) {
    int start = (s[0] == '-') ? 1 : 0;
    int digits = static_cast<int>(s.size()) - start;

    if (digits <= MAX_EXPONENT) return true;
    if (digits > MAX_EXPONENT + 1) return false;
    if (s[start] != '1') return false;
    for (int i = start + 1; i < static_cast<int>(s.size()); ++i) {
        if (s[i] != '0') return false;
    }
    return true;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int cases = 0;
    while (true) {
        string line = inf.readLine("[A-Z0-9\\-]{1,100002}", "line");
        if (line == "END") break;

        ++cases;
        ensuref(cases <= MAX_CASES, "too many test cases: %d", cases);
        setTestCase(cases);

        ensuref(isCanonicalInteger(line), "N is not a canonical integer: %s", line.c_str());
        ensuref(withinMagnitudeBound(line), "|N| exceeds 10^100000: %s", line.c_str());
    }

    inf.readEof();
}

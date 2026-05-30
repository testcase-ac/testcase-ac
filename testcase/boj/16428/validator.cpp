#include "testlib.h"
#include <cctype>
#include <string>
using namespace std;

bool isValidBigint(const string& s, bool allowZero) {
    if (s.empty()) return false;
    int start = 0;
    if (s[0] == '-') start = 1;
    if (start == (int)s.size()) return false;
    if (s[start] == '0' && start == 1) return false;
    if (s[start] == '0' && (int)s.size() > start + 1) return false;
    if (s[start] == '0' && !allowZero) return false;

    for (int i = start; i < (int)s.size(); ++i) {
        if (!isdigit(s[i])) return false;
    }

    int digits = (int)s.size() - start;
    if (digits <= 10000) return true;
    if (digits > 10001) return false;

    if (s[start] != '1') return false;
    for (int i = start + 1; i < (int)s.size(); ++i) {
        if (s[i] != '0') return false;
    }
    return true;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string A = inf.readToken("[^ ]{1,10002}", "A");
    inf.readSpace();
    string B = inf.readToken("[^ \n]{1,10002}", "B");
    inf.readEoln();

    ensuref(isValidBigint(A, true),
            "A is not a valid integer in [-10^10000, 10^10000], got: '%s'",
            A.c_str());
    ensuref(isValidBigint(B, false),
            "B is not a valid nonzero integer in [-10^10000, 10^10000], got: '%s'",
            B.c_str());

    inf.readEof();
}

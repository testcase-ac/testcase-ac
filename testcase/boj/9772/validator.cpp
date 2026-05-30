#include "testlib.h"
#include <cctype>
#include <string>
using namespace std;

bool readDigits(const string& s, int& pos) {
    int start = pos;
    while (pos < (int)s.size() && isdigit((unsigned char)s[pos])) {
        ++pos;
    }
    return pos > start;
}

bool isCanonicalReal(const string& s) {
    int pos = 0;
    if (pos < (int)s.size() && (s[pos] == '+' || s[pos] == '-')) {
        ++pos;
    }

    bool hasDigits = false;
    if (pos < (int)s.size() && s[pos] == '.') {
        ++pos;
        hasDigits = readDigits(s, pos);
    } else if (pos < (int)s.size() && s[pos] == '0') {
        ++pos;
        hasDigits = true;
        if (pos < (int)s.size() && isdigit((unsigned char)s[pos])) {
            return false;
        }
        if (pos < (int)s.size() && s[pos] == '.') {
            ++pos;
            if (!readDigits(s, pos)) {
                return false;
            }
        }
    } else {
        hasDigits = readDigits(s, pos);
        if (pos < (int)s.size() && s[pos] == '.') {
            ++pos;
            if (!readDigits(s, pos)) {
                return false;
            }
        }
    }

    if (!hasDigits) {
        return false;
    }

    if (pos < (int)s.size() && (s[pos] == 'e' || s[pos] == 'E')) {
        ++pos;
        if (pos < (int)s.size() && (s[pos] == '+' || s[pos] == '-')) {
            ++pos;
        }
        if (!readDigits(s, pos)) {
            return false;
        }
    }

    return pos == (int)s.size();
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAX_POINTS = 100000; // CHECK: practical cap; the statement gives no line count bound.
    const int MAX_TOKEN_LENGTH = 100; // CHECK: practical cap for unbounded real-number tokens.
    int cnt = 0;

    while (true) {
        string sx = inf.readToken("[^ ]+", "x");
        inf.readSpace();
        string sy = inf.readToken("[^ ]+", "y");
        inf.readEoln();

        ensuref((int)sx.size() <= MAX_TOKEN_LENGTH, "x token is too long");
        ensuref((int)sy.size() <= MAX_TOKEN_LENGTH, "y token is too long");
        ensuref(isCanonicalReal(sx), "x is not a real number: %s", sx.c_str());
        ensuref(isCanonicalReal(sy), "y is not a real number: %s", sy.c_str());

        if (sx == "0" && sy == "0") {
            break;
        }

        ++cnt;
        ensuref(cnt <= MAX_POINTS, "too many points before terminating 0 0");
    }

    inf.readEof();
}

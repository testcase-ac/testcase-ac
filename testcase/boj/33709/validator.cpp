#include "testlib.h"

#include <string>

using namespace std;

bool isDelimiter(char c) {
    return c == '.' || c == '|' || c == ':' || c == '#';
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "N");
    inf.readEoln();

    string slogan = inf.readLine("[^]{1,1000}", "slogan");
    ensuref((int)slogan.size() == n, "slogan length %d does not match N=%d",
            (int)slogan.size(), n);
    ensuref(!isDelimiter(slogan.front()), "slogan starts with a delimiter");
    ensuref(!isDelimiter(slogan.back()), "slogan ends with a delimiter");

    int value = 0;
    int digits = 0;
    bool leadingZero = false;
    for (int i = 0; i < n; ++i) {
        char c = slogan[i];
        if (isDelimiter(c)) {
            ensuref(digits > 0, "empty number before position %d", i + 1);
            ensuref(!leadingZero, "number ending before position %d has a leading zero", i + 1);
            ensuref(1 <= value && value <= 1000,
                    "number ending before position %d is out of range: %d", i + 1, value);
            value = 0;
            digits = 0;
            leadingZero = false;
            continue;
        }

        ensuref('0' <= c && c <= '9', "invalid character at position %d: %c", i + 1, c);
        if (digits == 0 && c == '0') {
            leadingZero = true;
        }
        value = value * 10 + (c - '0');
        ++digits;
    }

    ensuref(digits > 0, "slogan must end with a number");
    ensuref(!leadingZero, "last number has a leading zero");
    ensuref(1 <= value && value <= 1000, "last number is out of range: %d", value);

    inf.readEof();
}

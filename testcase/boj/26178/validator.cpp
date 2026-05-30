#include "testlib.h"

#include <algorithm>
#include <string>

using namespace std;

int gcdInt(int a, int b) {
    while (b != 0) {
        a %= b;
        swap(a, b);
    }
    return a;
}

int parseBoundedPositiveInt(const string& s, const char* name) {
    ensuref(!s.empty(), "%s is empty", name);
    ensuref(s.size() == 1 || s[0] != '0', "%s has a leading zero: %s", name, s.c_str());
    ensuref(s.size() <= 4, "%s is too long: %s", name, s.c_str());

    int value = 0;
    for (char ch : s) {
        ensuref('0' <= ch && ch <= '9', "%s contains a non-digit character: %s", name, s.c_str());
        value = value * 10 + (ch - '0');
    }
    ensuref(1 <= value && value <= 1000, "%s is out of range [1, 1000]: %d", name, value);
    return value;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string fraction = inf.readToken("[0-9]+/[0-9]+", "a/b");
    inf.readEoln();

    size_t slash = fraction.find('/');
    ensuref(slash != string::npos && fraction.find('/', slash + 1) == string::npos,
            "fraction must contain exactly one slash: %s", fraction.c_str());

    int a = parseBoundedPositiveInt(fraction.substr(0, slash), "a");
    int b = parseBoundedPositiveInt(fraction.substr(slash + 1), "b");
    ensuref(gcdInt(a, b) == 1, "a and b must be coprime: %d/%d", a, b);

    inf.readEof();
}

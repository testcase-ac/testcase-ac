#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

namespace {

const string LOWER = "roygbiv";
const string UPPER = "ROYGBIV";
const string LETTERS = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
const string NON_RAINBOW = "acdefhjklmnpqstuwxzACDEFHJKLMNPQSTUWXZ";

void appendAll(string& s, const string& chars) {
    vector<char> v(chars.begin(), chars.end());
    shuffle(v.begin(), v.end());
    for (char c : v) s += c;
}

void fillToLength(string& s, int n, const string& alphabet) {
    while (static_cast<int>(s.size()) < n) {
        s += rnd.any(alphabet);
    }
}

void trimAndShuffle(string& s, int n) {
    shuffle(s.begin(), s.end());
    if (static_cast<int>(s.size()) > n) s.resize(n);
}

string missingOne(const string& required, const string& filler, int n) {
    string chars = required;
    chars.erase(chars.begin() + rnd.next(static_cast<int>(chars.size())));

    string s;
    appendAll(s, chars);
    fillToLength(s, n, filler);
    trimAndShuffle(s, n);
    return s;
}

}  // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(8);
    int n = rnd.next(1, 30);
    if (rnd.next(10) == 0) n = rnd.next(31, 100);

    string s;
    if (mode == 0) {
        n = max(n, 7);
        appendAll(s, LOWER);
        fillToLength(s, n, "abcdefghijklmnopqrstuvwxyz");
    } else if (mode == 1) {
        n = max(n, 7);
        appendAll(s, UPPER);
        fillToLength(s, n, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    } else if (mode == 2) {
        n = max(n, 14);
        appendAll(s, LOWER);
        appendAll(s, UPPER);
        fillToLength(s, n, LETTERS);
    } else if (mode == 3) {
        fillToLength(s, n, NON_RAINBOW);
    } else if (mode == 4) {
        n = max(n, 6);
        s = missingOne(LOWER, "abcdefghijklmnopqrstuvwxyz", n);
    } else if (mode == 5) {
        n = max(n, 6);
        s = missingOne(UPPER, "ABCDEFGHIJKLMNOPQRSTUVWXYZ", n);
    } else if (mode == 6) {
        n = max(n, 13);
        appendAll(s, LOWER);
        string almostUpper = UPPER;
        almostUpper.erase(almostUpper.begin() + rnd.next(static_cast<int>(almostUpper.size())));
        appendAll(s, almostUpper);
        fillToLength(s, n, LETTERS);
    } else {
        fillToLength(s, n, LETTERS);
    }

    trimAndShuffle(s, n);

    println(n);
    println(s);

    return 0;
}

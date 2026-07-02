#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string repeatToLength(const string& pattern, int length) {
    string result;
    result.reserve(length);
    while ((int)result.size() < length) {
        result += pattern;
    }
    result.resize(length);
    return result;
}

string randomPattern(int length, const string& alphabet) {
    string pattern;
    pattern.reserve(length);
    for (int i = 0; i < length; ++i) {
        pattern += rnd.any(alphabet);
    }
    return pattern;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int mode = rnd.next(0, 5);
    string s;

    if (mode == 0) {
        int n = rnd.next(1, 30);
        s.assign(n, char('a' + rnd.next(0, 2)));
    } else if (mode == 1) {
        int period = rnd.next(1, 8);
        int repeats = rnd.next(2, 12);
        string pattern = randomPattern(period, "abc");
        s = repeatToLength(pattern, period * repeats);
    } else if (mode == 2) {
        int period = rnd.next(1, 7);
        int n = rnd.next(period + 1, 40);
        string pattern = randomPattern(period, "abcd");
        s = repeatToLength(pattern, n);
    } else if (mode == 3) {
        int n = rnd.next(2, 35);
        s = randomPattern(n, "abc");
        int changes = rnd.next(1, min(4, n));
        for (int i = 0; i < changes; ++i) {
            int pos = rnd.next(0, n - 1);
            s[pos] = char('a' + rnd.next(0, 2));
        }
    } else if (mode == 4) {
        int n = rnd.next(1, 50);
        s = randomPattern(n, "abcdefghijklmnopqrstuvwxyz");
    } else {
        int n = rnd.next(1, 45);
        vector<char> chars;
        chars.reserve(n);
        for (int i = 0; i < n; ++i) {
            chars.push_back(char('a' + rnd.next(0, 4)));
        }
        shuffle(chars.begin(), chars.end());
        s.assign(chars.begin(), chars.end());
    }

    println(s);
    return 0;
}

#include "testlib.h"

#include <algorithm>
#include <string>

using namespace std;

bool isPalindrome(const string& s) {
    return equal(s.begin(), s.begin() + s.size() / 2, s.rbegin());
}

void forceNonPalindrome(string& s) {
    if (!isPalindrome(s)) return;

    int n = (int)s.size();
    if (n == 1) {
        s += char(s[0] == 'a' ? 'b' : 'a');
        return;
    }

    int pos = rnd.next(0, n / 2 - 1);
    char replacement = char('a' + rnd.next(0, 25));
    if (replacement == s[n - 1 - pos]) {
        replacement = char('a' + (replacement - 'a' + 1) % 26);
    }
    s[pos] = replacement;
}

string randomString(int n, char maxChar) {
    string s;
    for (int i = 0; i < n; ++i) {
        s += char('a' + rnd.next(0, maxChar - 'a'));
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 28);
    char maxChar = char('a' + rnd.next(1, 5));
    string s;

    if (mode == 0) {
        s = randomString(n, maxChar);
    } else if (mode == 1) {
        int prefixLen = rnd.next(1, n - 1);
        string half = randomString((prefixLen + 1) / 2, maxChar);
        string prefix = half;
        for (int i = prefixLen / 2 - 1; i >= 0; --i) prefix += half[i];

        s = prefix + randomString(n - prefixLen, maxChar);
        if (s[prefixLen - 1] == s[prefixLen]) {
            s[prefixLen] = char('a' + (s[prefixLen] - 'a' + 1) % (maxChar - 'a' + 1));
        }
    } else if (mode == 2) {
        s = randomString(n, maxChar);
        for (int i = 0; i < n / 2; ++i) s[n - 1 - i] = s[i];
        int pos = rnd.next(0, n / 2 - 1);
        s[n - 1 - pos] = char('a' + (s[pos] - 'a' + 1) % (maxChar - 'a' + 1));
    } else if (mode == 3) {
        string pattern = randomString(rnd.next(1, min(6, n - 1)), maxChar);
        for (int i = 0; i < n; ++i) s += pattern[i % (int)pattern.size()];
    } else if (mode == 4) {
        n = rnd.next(2, 8);
        s.assign(n, rnd.next(0, 1) ? 'a' : 'b');
        s[rnd.next(0, n - 1)] = char(s[0] == 'a' ? 'b' : 'a');
    } else {
        n = rnd.next(25, 80);
        s = randomString(n, 'z');
    }

    forceNonPalindrome(s);
    println(s);
    return 0;
}

#include "testlib.h"
#include <algorithm>
#include <string>

using namespace std;

string randomLowercase(int n) {
    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) {
        s.push_back(char('a' + rnd.next(26)));
    }
    return s;
}

string makePalindrome(string half, int n) {
    string s = half;
    int start = n % 2 == 0 ? int(half.size()) - 1 : int(half.size()) - 2;
    for (int i = start; i >= 0; --i) {
        s.push_back(half[i]);
    }
    return s;
}

string makeAkaraka(int n) {
    if (n == 1) {
        return string(1, char('a' + rnd.next(26)));
    }

    int halfLen = n / 2;
    string half = makeAkaraka(halfLen);
    string s = half;
    if (n % 2 == 1) {
        s.push_back(char('a' + rnd.next(26)));
    }
    string right = half;
    reverse(right.begin(), right.end());
    s += right;
    return s;
}

void mutateOne(string& s) {
    int pos = rnd.next(int(s.size()));
    char replacement = char('a' + rnd.next(26));
    if (replacement == s[pos]) {
        replacement = char('a' + (replacement - 'a' + 1) % 26);
    }
    s[pos] = replacement;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n;
    string s;

    if (mode == 0) {
        n = rnd.next(1, 30);
        s = makeAkaraka(n);
    } else if (mode == 1) {
        n = rnd.next(2, 30);
        string half = randomLowercase((n + 1) / 2);
        s = makePalindrome(half, n);
        if (n / 2 >= 2 && rnd.next(2) == 0) {
            mutateOne(s);
            reverse(s.begin(), s.end());
            s = makePalindrome(s.substr(0, (n + 1) / 2), n);
        }
    } else if (mode == 2) {
        n = rnd.next(2, 30);
        s = makeAkaraka(n);
        mutateOne(s);
    } else if (mode == 3) {
        n = rnd.next(1, 30);
        char c = char('a' + rnd.next(26));
        s.assign(n, c);
    } else {
        n = rnd.next(1, 30);
        s = randomLowercase(n);
    }

    println(s);
    return 0;
}

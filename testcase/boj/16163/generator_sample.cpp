#include "testlib.h"

#include <algorithm>
#include <string>

using namespace std;

char randomChar(int alphabetSize) {
    return char('A' + rnd.next(alphabetSize));
}

string randomString(int n, int alphabetSize) {
    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) s.push_back(randomChar(alphabetSize));
    return s;
}

string repeatedString(int n) {
    return string(n, randomChar(rnd.next(1, 5)));
}

string alternatingString(int n) {
    char a = randomChar(4);
    char b = randomChar(4);
    while (b == a) b = randomChar(4);

    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) s.push_back((i % 2 == 0) ? a : b);
    return s;
}

string palindromeString(int n) {
    string s(n, 'A');
    int alphabetSize = rnd.next(1, 6);
    for (int i = 0; i < (n + 1) / 2; ++i) {
        s[i] = randomChar(alphabetSize);
        s[n - 1 - i] = s[i];
    }
    return s;
}

string nearPalindromeString(int n) {
    string s = palindromeString(n);
    int changes = rnd.next(1, max(1, min(n, 4)));
    for (int i = 0; i < changes; ++i) {
        int pos = rnd.next(n);
        char c = randomChar(8);
        while (c == s[pos]) c = randomChar(8);
        s[pos] = c;
    }
    return s;
}

string blockString(int n) {
    string s;
    s.reserve(n);
    while ((int)s.size() < n) {
        int len = rnd.next(1, min(6, n - (int)s.size()));
        char c = randomChar(rnd.next(2, 7));
        s.append(len, c);
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n;
    if (rnd.next(10) == 0) {
        n = rnd.next(40, 120);
    } else {
        n = rnd.next(1, 30);
    }

    string s;
    if (mode == 0) {
        s = repeatedString(n);
    } else if (mode == 1) {
        s = alternatingString(n);
    } else if (mode == 2) {
        s = palindromeString(n);
    } else if (mode == 3) {
        s = nearPalindromeString(n);
    } else if (mode == 4) {
        s = blockString(n);
    } else {
        s = randomString(n, rnd.next(2, 27));
    }

    println(s);
    return 0;
}

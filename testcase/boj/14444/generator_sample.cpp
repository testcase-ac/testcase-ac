#include "testlib.h"
#include <algorithm>
#include <string>

using namespace std;

string randomString(int n, int alphabetSize) {
    string s;
    for (int i = 0; i < n; ++i) {
        s += char('a' + rnd.next(alphabetSize));
    }
    return s;
}

string randomPalindrome(int n, int alphabetSize) {
    string s(n, 'a');
    for (int i = 0; i < (n + 1) / 2; ++i) {
        char c = char('a' + rnd.next(alphabetSize));
        s[i] = c;
        s[n - 1 - i] = c;
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n = rnd.next(1, 30);
    int alphabetSize = rnd.next(1, 6);
    string s;

    if (mode == 0) {
        s = randomString(n, alphabetSize);
    } else if (mode == 1) {
        s = string(n, char('a' + rnd.next(alphabetSize)));
    } else if (mode == 2) {
        s = randomPalindrome(n, alphabetSize);
    } else if (mode == 3) {
        int coreLen = rnd.next(1, n);
        string core = randomPalindrome(coreLen, alphabetSize);
        int leftLen = rnd.next(0, n - coreLen);
        int rightLen = n - coreLen - leftLen;
        s = randomString(leftLen, alphabetSize) + core + randomString(rightLen, alphabetSize);
    } else if (mode == 4) {
        char a = char('a' + rnd.next(alphabetSize));
        char b = char('a' + rnd.next(alphabetSize));
        if (alphabetSize > 1) {
            while (b == a) b = char('a' + rnd.next(alphabetSize));
        }
        for (int i = 0; i < n; ++i) {
            s += (i % 2 == 0 ? a : b);
        }
    } else {
        s = randomPalindrome(n, alphabetSize);
        if (n >= 3) {
            int changes = rnd.next(1, min(3, n));
            for (int i = 0; i < changes; ++i) {
                int pos = rnd.next(n);
                s[pos] = char('a' + rnd.next(alphabetSize));
            }
        }
    }

    println(s);
    return 0;
}

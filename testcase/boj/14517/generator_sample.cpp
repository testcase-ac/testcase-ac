#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

char randomLower(int alphabetSize) {
    return char('a' + rnd.next(alphabetSize));
}

string randomString(int n, int alphabetSize) {
    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) {
        s.push_back(randomLower(alphabetSize));
    }
    return s;
}

string repeatedBlocks(int n, int alphabetSize) {
    string s;
    while ((int)s.size() < n) {
        char c = randomLower(alphabetSize);
        int remaining = n - (int)s.size();
        int blockSize = rnd.next(1, min(remaining, 6));
        s.append(blockSize, c);
    }
    return s;
}

string alternatingString(int n, int alphabetSize) {
    char a = randomLower(alphabetSize);
    char b = randomLower(alphabetSize);
    while (b == a && alphabetSize > 1) {
        b = randomLower(alphabetSize);
    }

    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) {
        s.push_back(i % 2 == 0 ? a : b);
    }
    return s;
}

string nearPalindrome(int n, int alphabetSize) {
    string s(n, 'a');
    for (int i = 0; i < (n + 1) / 2; ++i) {
        char c = randomLower(alphabetSize);
        s[i] = c;
        s[n - 1 - i] = c;
    }

    int changes = rnd.next(0, max(1, n / 5));
    for (int i = 0; i < changes; ++i) {
        int pos = rnd.next(n);
        s[pos] = randomLower(alphabetSize);
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n = rnd.next(1, 30);
    if (rnd.next(10) == 0) {
        n = rnd.next(31, 120);
    }

    int alphabetSize = rnd.next(1, 26);
    string s;

    if (mode == 0) {
        s.assign(n, randomLower(alphabetSize));
    } else if (mode == 1) {
        s = alternatingString(n, max(2, alphabetSize));
    } else if (mode == 2) {
        s = repeatedBlocks(n, alphabetSize);
    } else if (mode == 3) {
        s = nearPalindrome(n, alphabetSize);
    } else if (mode == 4) {
        s = randomString(n, min(alphabetSize, rnd.next(1, 4)));
    } else {
        s = randomString(n, alphabetSize);
    }

    println(s);
    return 0;
}

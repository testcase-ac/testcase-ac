#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

char randomLowerExcept(char blocked) {
    char c = static_cast<char>('a' + rnd.next(26));
    if (c == blocked) c = static_cast<char>('a' + (c - 'a' + 1) % 26);
    return c;
}

string alternatingString(int n) {
    string s;
    s.reserve(n);
    char a = static_cast<char>('a' + rnd.next(26));
    char b = randomLowerExcept(a);
    for (int i = 0; i < n; ++i) s.push_back(i % 2 == 0 ? a : b);
    return s;
}

string runString(int n) {
    string s;
    s.reserve(n);
    char last = static_cast<char>('a' + rnd.next(26));
    while (static_cast<int>(s.size()) < n) {
        int remaining = n - static_cast<int>(s.size());
        int len = rnd.next(1, min(remaining, 6));
        char c = rnd.next(0, 3) == 0 ? last : randomLowerExcept(last);
        s.append(len, c);
        last = c;
    }
    return s;
}

string sparseDuplicateString(int n) {
    string s = alternatingString(n);
    if (n >= 2) {
        int pos = rnd.next(0, n - 2);
        s[pos + 1] = s[pos];
    }
    return s;
}

string mixedAlphabetString(int n) {
    string s;
    s.reserve(n);
    int alphabetSize = rnd.next(2, 8);
    for (int i = 0; i < n; ++i) {
        s.push_back(static_cast<char>('a' + rnd.next(alphabetSize)));
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 40);
    string s;

    if (mode == 0) {
        s = alternatingString(n);
    } else if (mode == 1) {
        s.assign(n, static_cast<char>('a' + rnd.next(26)));
    } else if (mode == 2) {
        s = sparseDuplicateString(n);
    } else if (mode == 3) {
        s = runString(n);
    } else if (mode == 4) {
        s = mixedAlphabetString(n);
    } else {
        vector<string> anchors = {
            "success",
            "failure",
            "aaaa",
            "ababcc",
            "zzxyyx",
            "abcddcba",
        };
        s = rnd.any(anchors);
        if (rnd.next(0, 1)) {
            int extra = rnd.next(0, 12);
            string tail = alternatingString(extra);
            s += tail;
        }
    }

    println(static_cast<int>(s.size()));
    println(s);
    return 0;
}

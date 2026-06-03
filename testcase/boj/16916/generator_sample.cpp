#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>
using namespace std;

string randomString(int len, const string& alphabet) {
    string result;
    result.reserve(len);
    for (int i = 0; i < len; ++i) {
        result += rnd.any(alphabet);
    }
    return result;
}

char differentFrom(char c, const string& alphabet) {
    char next = rnd.any(alphabet);
    while (next == c) {
        next = rnd.any(alphabet);
    }
    return next;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const string smallAlphabet = "abc";
    const string alphabet = "abcdefghijklmnopqrstuvwxyz";
    int mode = rnd.next(0, 5);

    string s;
    string p;

    if (mode == 0) {
        int n = rnd.next(1, 30);
        s = randomString(n, smallAlphabet);
        int l = rnd.next(0, n - 1);
        int r = rnd.next(l, n - 1);
        p = s.substr(l, r - l + 1);
    } else if (mode == 1) {
        int n = rnd.next(1, 24);
        int extra = rnd.next(1, 6);
        s = randomString(n, smallAlphabet);
        p = randomString(n + extra, smallAlphabet);
        p[rnd.next(0, (int)p.size() - 1)] = 'd';
    } else if (mode == 2) {
        int n = rnd.next(2, 30);
        s = randomString(n, "ab");
        int len = rnd.next(1, min(12, n));
        int start = rnd.next(0, n - len);
        p = s.substr(start, len);
        p[rnd.next(0, len - 1)] = 'c';
    } else if (mode == 3) {
        int n = rnd.next(1, 30);
        char fill = rnd.any(smallAlphabet);
        s.assign(n, fill);
        int len = rnd.next(1, n);
        p.assign(len, fill);
        if (rnd.next(0, 1) == 0 && len > 1) {
            p[len - 1] = differentFrom(fill, smallAlphabet);
        }
    } else if (mode == 4) {
        int repeats = rnd.next(2, 7);
        string block = randomString(rnd.next(2, 5), "ab");
        for (int i = 0; i < repeats; ++i) {
            s += block;
        }
        s += differentFrom(block.back(), smallAlphabet);
        int len = rnd.next(2, min(18, (int)s.size()));
        int start = rnd.next(0, (int)s.size() - len);
        p = s.substr(start, len);
    } else {
        int prefix = rnd.next(0, 8);
        int middle = rnd.next(1, 8);
        int suffix = rnd.next(0, 8);
        s = randomString(prefix, alphabet);
        s += randomString(middle, "xyz");
        s += randomString(suffix, alphabet);
        p = randomString(rnd.next(1, 12), "abc");
    }

    println(s);
    println(p);

    return 0;
}

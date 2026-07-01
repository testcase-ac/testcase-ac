#include "testlib.h"

#include <algorithm>
#include <string>

using namespace std;

string randomString(int len, char lo = 'a', char hi = 'z') {
    string s;
    for (int i = 0; i < len; ++i) {
        s += char(rnd.next(int(lo), int(hi)));
    }
    return s;
}

string repeatedString(int len, char ch) {
    return string(len, ch);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    string s1, s2;
    int mode = rnd.next(0, 7);

    if (mode == 0) {
        int len = rnd.next(1, 30);
        s1 = randomString(len, 'a', char('a' + rnd.next(0, 4)));
        s2 = s1;
    } else if (mode == 1) {
        int len1 = rnd.next(1, 30);
        int len2 = rnd.next(1, 30);
        s1 = "a" + randomString(len1 - 1, 'a', 'f');
        s2 = "z" + randomString(len2 - 1, 'u', 'z');
    } else if (mode == 2) {
        int prefixLen = rnd.next(1, 24);
        string prefix = randomString(prefixLen, 'a', 'd');
        s1 = prefix + randomString(rnd.next(1, 12), 'e', 'm');
        s2 = prefix + randomString(rnd.next(1, 12), 'n', 'z');
    } else if (mode == 3) {
        int prefixLen = rnd.next(1, 25);
        string prefix = randomString(prefixLen, 'a', 'h');
        s1 = prefix;
        s2 = prefix + randomString(rnd.next(1, 20), 'i', 'z');
        if (rnd.next(0, 1)) {
            swap(s1, s2);
        }
    } else if (mode == 4) {
        int prefixLen = rnd.next(1, 18);
        int suffixLen = rnd.next(1, 12);
        string prefix = randomString(prefixLen, 'a', 'c');
        string suffix = randomString(suffixLen, 'x', 'z');
        s1 = prefix + randomString(rnd.next(1, 8), 'd', 'm') + suffix;
        s2 = prefix + randomString(rnd.next(1, 8), 'n', 'w') + suffix;
    } else if (mode == 5) {
        char a = char('a' + rnd.next(0, 25));
        char b = char('a' + rnd.next(0, 25));
        while (b == a) {
            b = char('a' + rnd.next(0, 25));
        }
        s1 = repeatedString(rnd.next(1, 100), a);
        s2 = repeatedString(rnd.next(1, 100), b);
    } else if (mode == 6) {
        int len1 = rnd.next(70, 100);
        int len2 = rnd.next(70, 100);
        int prefixLen = rnd.next(0, min(len1, len2) - 1);
        string prefix = randomString(prefixLen, 'a', 'b');
        s1 = prefix + randomString(len1 - prefixLen, 'c', 'm');
        s2 = prefix + randomString(len2 - prefixLen, 'n', 'z');
    } else {
        int len1 = rnd.next(1, 30);
        int len2 = rnd.next(1, 30);
        s1 = randomString(len1);
        s2 = randomString(len2);
    }

    println(s1);
    println(s2);
    return 0;
}

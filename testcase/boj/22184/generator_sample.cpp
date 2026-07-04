#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string randomString(int len, const string& alphabet) {
    string s;
    s.reserve(len);
    for (int i = 0; i < len; ++i) {
        s.push_back(rnd.any(alphabet));
    }
    return s;
}

string mutateOne(string s, const string& alphabet) {
    int pos = rnd.next(0, int(s.size()) - 1);
    char c = s[pos];
    while (c == s[pos]) {
        c = rnd.any(alphabet);
    }
    s[pos] = c;
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const string smallAlphabet = "abc";
    const string fullAlphabet = "abcdefghijklmnopqrstuvwxyz";

    int t = rnd.next(12, 30);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = tc < 8 ? tc : rnd.next(0, 7);
        long long L;
        int m;
        string s1, s2;

        if (mode == 0) {
            int a = rnd.next(1, 8);
            int b = rnd.next(1, 8);
            L = rnd.next(a + b, a + b + 20);
            m = rnd.next(1, 10000);
            s1 = randomString(a, smallAlphabet);
            s2 = randomString(b, smallAlphabet);
        } else if (mode == 1) {
            int len = rnd.next(1, 14);
            L = rnd.next(len, len + 10);
            m = rnd.next(2, 10000);
            s1 = randomString(len, smallAlphabet);
            s2 = s1;
        } else if (mode == 2) {
            int shortLen = rnd.next(1, 6);
            int extraLen = rnd.next(1, 8);
            s1 = randomString(shortLen, smallAlphabet);
            s2 = s1 + randomString(extraLen, smallAlphabet);
            L = rnd.next(int(s2.size()), int(s1.size() + s2.size()) + 10);
            m = rnd.next(2, 10000);
        } else if (mode == 3) {
            int shortLen = rnd.next(1, 6);
            int extraLen = rnd.next(1, 8);
            s1 = randomString(shortLen, smallAlphabet);
            s2 = randomString(extraLen, smallAlphabet) + s1;
            L = rnd.next(int(s2.size()), int(s1.size() + s2.size()) + 10);
            m = rnd.next(2, 10000);
        } else if (mode == 4) {
            int a = rnd.next(4, 12);
            int b = rnd.next(4, 12);
            L = rnd.next(max(a, b), a + b - 1);
            s1 = randomString(a, smallAlphabet);
            s2 = randomString(b, smallAlphabet);
            m = rnd.next(2, 10000);
        } else if (mode == 5) {
            int len = rnd.next(3, 12);
            string base = randomString(len, smallAlphabet);
            s1 = base;
            s2 = mutateOne(base, smallAlphabet);
            L = rnd.next(len, len + 5);
            m = rnd.next(2, 10000);
        } else if (mode == 6) {
            int a = rnd.next(12, 25);
            int b = rnd.next(12, 25);
            L = rnd.next(1, min(a, b) - 1);
            s1 = randomString(a, fullAlphabet);
            s2 = randomString(b, fullAlphabet);
            m = rnd.next(1, 10000);
        } else {
            int len = rnd.next(20, 200);
            L = rnd.next(1000000LL, 1000000000LL);
            m = rnd.next(1, 10000);
            s1 = randomString(len, fullAlphabet);
            if (rnd.next(0, 1) == 0) {
                s2 = s1;
            } else {
                s2 = randomString(rnd.next(20, 200), fullAlphabet);
            }
        }

        if (rnd.next(0, 1) == 1) {
            swap(s1, s2);
        }

        println(L, m);
        println(s1);
        println(s2);
    }

    return 0;
}

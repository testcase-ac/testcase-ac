#include "testlib.h"

#include <algorithm>
#include <string>

using namespace std;

string randomString(int n, const string& alphabet) {
    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) {
        s += rnd.any(alphabet);
    }
    return s;
}

string periodicWindow(const string& base, int offset, int len) {
    string s;
    s.reserve(len);
    for (int i = 0; i < len; ++i) {
        s += base[(offset + i) % (int)base.size()];
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    string s;

    if (mode == 0) {
        int n = rnd.next(1, 25);
        char c = char('a' + rnd.next(0, 25));
        s.assign(n, c);
    } else if (mode == 1) {
        int p = rnd.next(1, 9);
        string base = randomString(p, "abcde");
        int repeats = rnd.next(1, 5);
        s = periodicWindow(base, 0, p * repeats);
    } else if (mode == 2) {
        int p = rnd.next(2, 10);
        string base = randomString(p, "abcd");
        int len = rnd.next(p + 1, min(30, 4 * p + 3));
        int offset = rnd.next(0, p - 1);
        s = periodicWindow(base, offset, len);
    } else if (mode == 3) {
        int p = rnd.next(2, 8);
        string base = randomString(p, "abc");
        int len = rnd.next(p + 2, min(30, 4 * p + 5));
        s = periodicWindow(base, 0, len);
        int pos = rnd.next(0, len - 1);
        char replacement = char('a' + rnd.next(0, 2));
        if (replacement == s[pos]) {
            replacement = char('a' + (replacement - 'a' + 1) % 3);
        }
        s[pos] = replacement;
    } else if (mode == 4) {
        string middle = randomString(rnd.next(1, 8), "abcd");
        string border = randomString(rnd.next(1, 8), "abcd");
        s = border + middle + border;
    } else {
        int n = rnd.next(2, 30);
        string alphabet = rnd.next(0, 1) == 0 ? "abcdefghijklmnopqrstuvwxyz" : "abcdef";
        s = randomString(n, alphabet);
    }

    println((int)s.size());
    println(s);

    return 0;
}

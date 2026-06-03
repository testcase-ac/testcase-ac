#include "testlib.h"

#include <algorithm>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n = rnd.next(1, 30);
    string s;

    if (mode == 0) {
        s.assign(n, (char)('a' + rnd.next(0, 25)));
    } else if (mode == 1) {
        char a = 'a' + rnd.next(0, 25);
        char b = 'a' + rnd.next(0, 24);
        if (b >= a) ++b;
        for (int i = 0; i < n; ++i) s += (i % 2 == 0 ? a : b);
    } else if (mode == 2) {
        int half = rnd.next(1, 15);
        string left;
        for (int i = 0; i < half; ++i) left += (char)('a' + rnd.next(0, 5));
        s = left;
        if (rnd.next(0, 1)) s += (char)('a' + rnd.next(0, 5));
        reverse(left.begin(), left.end());
        s += left;
    } else if (mode == 3) {
        s.assign(n, (char)('a' + rnd.next(0, 2)));
        int changes = rnd.next(1, max(1, n / 4));
        for (int i = 0; i < changes; ++i) s[rnd.next(0, n - 1)] = (char)('a' + rnd.next(0, 25));
    } else if (mode == 4) {
        int blocks = rnd.next(2, 8);
        for (int i = 0; i < blocks; ++i) {
            int len = rnd.next(1, 5);
            char c = 'a' + rnd.next(0, 5);
            s.append(len, c);
        }
    } else if (mode == 5) {
        n = rnd.next(1, 30);
        int alphabet = rnd.next(1, 8);
        for (int i = 0; i < n; ++i) s += (char)('a' + rnd.next(0, alphabet - 1));
    } else if (mode == 6) {
        n = rnd.next(2, 30);
        for (int i = 0; i < n; ++i) s += (char)('a' + (i % 3));
        int start = rnd.next(0, n - 1);
        int len = rnd.next(1, n - start);
        reverse(s.begin() + start, s.begin() + start + len);
    } else {
        n = rnd.next(80, 300);
        int alphabet = rnd.next(2, 4);
        for (int i = 0; i < n; ++i) s += (char)('a' + rnd.next(0, alphabet - 1));
    }

    println(s);
    return 0;
}

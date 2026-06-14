#include "testlib.h"

#include <string>

using namespace std;

int oddLength(int lo, int hi) {
    int n = rnd.next(lo, hi);
    if (n % 2 == 0) ++n;
    if (n > hi) n -= 2;
    return n;
}

char targetChar(int i) {
    return i % 2 == 0 ? 'I' : 'O';
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = 99;
    } else if (mode == 2) {
        n = oddLength(1, 9);
    } else {
        n = oddLength(3, 29);
    }

    string s(n, 'A');
    if (mode == 0 || mode == 1) {
        for (int i = 0; i < n; ++i) s[i] = targetChar(i);
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) s[i] = targetChar(i) == 'I' ? 'O' : 'I';
    } else if (mode == 3) {
        char c = rnd.next(0, 1) ? 'I' : 'O';
        if (rnd.next(0, 3) == 0) c = char('A' + rnd.next(0, 25));
        s.assign(n, c);
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) s[i] = targetChar(i);
        int changes = rnd.next(1, n);
        for (int k = 0; k < changes; ++k) {
            int pos = rnd.next(0, n - 1);
            char c = char('A' + rnd.next(0, 25));
            while (c == targetChar(pos)) c = char('A' + rnd.next(0, 25));
            s[pos] = c;
        }
    } else if (mode == 5) {
        string alphabet = "IOJ";
        if (rnd.next(0, 1)) alphabet += "ABC";
        for (int i = 0; i < n; ++i) s[i] = rnd.any(alphabet);
    } else {
        for (int i = 0; i < n; ++i) s[i] = char('A' + rnd.next(0, 25));
    }

    println(n);
    println(s);
    return 0;
}

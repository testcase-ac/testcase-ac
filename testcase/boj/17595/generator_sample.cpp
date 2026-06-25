#include "testlib.h"

#include <algorithm>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(2, 30);
    string s;

    if (mode == 0) {
        char c = char('a' + rnd.next(0, 25));
        s.assign(n, c);
    } else if (mode == 1) {
        char a = char('a' + rnd.next(0, 25));
        char b = char('a' + rnd.next(0, 24));
        if (b >= a) ++b;
        for (int i = 0; i < n; ++i) {
            s += (i % 2 == 0 ? a : b);
        }
    } else if (mode == 2) {
        int alphabet = rnd.next(2, 8);
        for (int i = 0; i < n; ++i) {
            s += char('a' + rnd.next(0, alphabet - 1));
        }
    } else if (mode == 3) {
        int runs = rnd.next(2, min(10, n));
        string letters = "abcdefghijklmnopqrstuvwxyz";
        shuffle(letters.begin(), letters.end());
        int remaining = n;
        for (int i = 0; i < runs; ++i) {
            int len = (i + 1 == runs) ? remaining : rnd.next(1, remaining - (runs - i - 1));
            s.append(len, letters[i]);
            remaining -= len;
        }
    } else if (mode == 4) {
        int alphabet = rnd.next(2, min(26, n));
        for (int i = 0; i < alphabet; ++i) {
            s += char('a' + i);
        }
        while ((int)s.size() < n) {
            s += char('a' + rnd.next(0, alphabet - 1));
        }
        shuffle(s.begin(), s.end());
    } else if (mode == 5) {
        int half = n / 2;
        for (int i = 0; i < half; ++i) {
            s += char('a' + rnd.next(0, 5));
        }
        string tail = s;
        reverse(tail.begin(), tail.end());
        s += tail;
        if ((int)s.size() < n) {
            s += char('a' + rnd.next(0, 5));
        }
    } else {
        string letters = "abcdefghijklmnopqrstuvwxyz";
        shuffle(letters.begin(), letters.end());
        int take = min(n, 26);
        s = letters.substr(0, take);
        while ((int)s.size() < n) {
            s += rnd.any(letters);
        }
    }

    println(s);
    return 0;
}

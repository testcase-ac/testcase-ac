#include "testlib.h"

#include <string>

using namespace std;

char randomLetter() {
    const string letters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    return rnd.any(letters);
}

char differentLetter(char c) {
    char next = randomLetter();
    while (next == c) {
        next = randomLetter();
    }
    return next;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode == 5) {
        n = rnd.next(60, 120);
    } else {
        n = rnd.next(2, 30);
    }

    string original;
    original.reserve(n);
    for (int i = 0; i < n; ++i) {
        if (mode == 3) {
            original += rnd.next(0, 1) == 0 ? 'a' : 'A';
        } else if (mode == 4) {
            original += char('A' + rnd.next(0, 3));
        } else {
            original += randomLetter();
        }
    }

    string rewritten = original;
    if (mode == 1) {
        int changes = rnd.next(1, n);
        for (int i = 0; i < changes; ++i) {
            int pos = rnd.next(0, n - 1);
            rewritten[pos] = differentLetter(rewritten[pos]);
        }
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            rewritten[i] = differentLetter(original[i]);
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 1) == 1) {
                rewritten[i] = original[i] == 'a' ? 'A' : 'a';
            }
        }
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) {
            if (rnd.next() < 0.35) {
                rewritten[i] = differentLetter(original[i]);
            }
        }
    } else if (mode == 5) {
        for (int i = 0; i < n; ++i) {
            if (i % rnd.next(2, 7) == 0) {
                rewritten[i] = differentLetter(original[i]);
            }
        }
    }

    println(n);
    println(original);
    println(rewritten);

    return 0;
}

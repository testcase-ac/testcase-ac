#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string makeLetters(int total, int mode) {
    string letters;
    letters.reserve(total);

    if (mode == 0) {
        char ch = char('a' + rnd.next(26));
        letters.assign(total, ch);
    } else if (mode == 1) {
        string alphabet = "abc";
        for (int i = 0; i < total; ++i) {
            letters.push_back(alphabet[rnd.wnext(static_cast<int>(alphabet.size()), -2)]);
        }
    } else if (mode == 2) {
        int high = rnd.next(1, 25);
        for (int i = 0; i < total; ++i) {
            letters.push_back(char('a' + rnd.next(high + 1)));
        }
    } else if (mode == 3) {
        for (int i = 0; i < total; ++i) {
            letters.push_back(char('z' - (i % 26)));
        }
        shuffle(letters.begin(), letters.end());
    } else {
        for (int i = 0; i < total; ++i) {
            letters.push_back(char('a' + rnd.next(26)));
        }
    }

    return letters;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n;
    int l;

    if (mode == 0) {
        n = rnd.next(1, 12);
        l = rnd.next(1, 20);
    } else if (mode == 1) {
        n = rnd.next(2, 18);
        l = 1;
    } else if (mode == 2) {
        n = rnd.next(2, 10);
        l = rnd.next(12, 30);
    } else if (mode == 3) {
        n = rnd.next(8, 20);
        l = rnd.next(2, 12);
    } else {
        n = rnd.next(2, 16);
        l = rnd.next(2, 18);
    }

    int kMode = rnd.next(4);
    int k;
    if (kMode == 0) {
        k = 1;
    } else if (kMode == 1) {
        k = n;
    } else if (kMode == 2) {
        k = (n + 1) / 2;
    } else {
        k = rnd.next(1, n);
    }

    string letters = makeLetters(n * l, mode);
    println(n, l, k);
    println(letters);

    return 0;
}

#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

char fillerChar() {
    const string letters = "ABDEFGHIJKLMNOQRSTUVWXYZ";
    return rnd.any(letters);
}

string randomFillerString(int n) {
    string s;
    for (int i = 0; i < n; ++i) {
        s += fillerChar();
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(1, 30);
    if (rnd.next(0, 9) == 0) {
        n = rnd.next(31, 100);
    }

    string s;

    if (mode == 0) {
        s = randomFillerString(n);
    } else if (mode == 1) {
        s = randomFillerString(n);
        int countP = rnd.next(1, n);
        vector<int> pos(n);
        for (int i = 0; i < n; ++i) {
            pos[i] = i;
        }
        shuffle(pos.begin(), pos.end());
        for (int i = 0; i < countP; ++i) {
            s[pos[i]] = 'P';
        }
    } else if (mode == 2) {
        s = randomFillerString(n);
        int countC = rnd.next(1, n);
        vector<int> pos(n);
        for (int i = 0; i < n; ++i) {
            pos[i] = i;
        }
        shuffle(pos.begin(), pos.end());
        for (int i = 0; i < countC; ++i) {
            s[pos[i]] = 'C';
        }
    } else if (mode == 3) {
        if (n == 1) {
            n = 2;
        }
        int pairs = rnd.next(1, max(1, n / 2));
        s = randomFillerString(n);
        vector<int> pos(n);
        for (int i = 0; i < n; ++i) {
            pos[i] = i;
        }
        shuffle(pos.begin(), pos.end());
        for (int i = 0; i < pairs; ++i) {
            s[pos[2 * i]] = 'P';
            s[pos[2 * i + 1]] = 'C';
        }
    } else if (mode == 4) {
        int countP = rnd.next(1, n);
        int countC = rnd.next(1, n);
        while (countP + countC > n) {
            if (countP > countC) {
                --countP;
            } else {
                --countC;
            }
        }
        s = randomFillerString(n);
        vector<int> pos(n);
        for (int i = 0; i < n; ++i) {
            pos[i] = i;
        }
        shuffle(pos.begin(), pos.end());
        for (int i = 0; i < countP; ++i) {
            s[pos[i]] = 'P';
        }
        for (int i = 0; i < countC; ++i) {
            s[pos[countP + i]] = 'C';
        }
    } else if (mode == 5) {
        for (int i = 0; i < n; ++i) {
            s += rnd.any(string("PC"));
        }
    } else {
        const string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        for (int i = 0; i < n; ++i) {
            s += rnd.any(alphabet);
        }
    }

    println(n);
    println(s);

    return 0;
}

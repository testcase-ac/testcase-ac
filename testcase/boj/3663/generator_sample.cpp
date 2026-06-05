#include "testlib.h"

#include <string>

using namespace std;

char randomNonA() {
    string letters = "BCDEFGHIJKLMNOPQRSTUVWXYZ";
    return rnd.any(letters);
}

string randomWord(int n, int mode) {
    string s(n, 'A');

    if (mode == 0) {
        for (int i = 0; i < n; ++i) {
            s[i] = rnd.any(string("ABCDEFGHIJKLMNOPQRSTUVWXYZ"));
        }
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) {
            s[i] = rnd.next(100) < 75 ? 'A' : randomNonA();
        }
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            s[i] = rnd.next(100) < 65 ? rnd.any(string("AZ")) : randomNonA();
        }
    } else if (mode == 3) {
        int leftLen = rnd.next(0, n);
        int rightStart = rnd.next(leftLen, n);
        for (int i = 0; i < leftLen; ++i) {
            s[i] = randomNonA();
        }
        for (int i = rightStart; i < n; ++i) {
            s[i] = randomNonA();
        }
    } else {
        int blocks = rnd.next(1, 5);
        for (int block = 0; block < blocks; ++block) {
            int l = rnd.next(0, n - 1);
            int r = rnd.next(l, n - 1);
            for (int i = l; i <= r; ++i) {
                s[i] = randomNonA();
            }
        }
    }

    if (rnd.next(100) < 20) {
        s[0] = randomNonA();
    }
    if (rnd.next(100) < 20) {
        s[n - 1] = randomNonA();
    }

    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 20);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int sizeMode = rnd.next(100);
        int n;
        if (sizeMode < 60) {
            n = rnd.next(1, 12);
        } else if (sizeMode < 90) {
            n = rnd.next(13, 60);
        } else {
            n = rnd.next(61, 1000);
        }

        println(randomWord(n, rnd.next(0, 4)));
    }

    return 0;
}

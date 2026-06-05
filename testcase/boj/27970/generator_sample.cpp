#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(1, 80);
    string s;

    if (mode == 0) {
        s.assign(n, rnd.next(0, 1) == 0 ? 'O' : 'X');
    } else if (mode == 1) {
        char first = rnd.next(0, 1) == 0 ? 'O' : 'X';
        for (int i = 0; i < n; ++i) {
            s += (i % 2 == 0 ? first : (first == 'O' ? 'X' : 'O'));
        }
    } else if (mode == 2) {
        char cur = rnd.next(0, 1) == 0 ? 'O' : 'X';
        while ((int)s.size() < n) {
            int len = rnd.next(1, 8);
            for (int i = 0; i < len && (int)s.size() < n; ++i) {
                s += cur;
            }
            if (rnd.next(0, 2) != 0) {
                cur = (cur == 'O' ? 'X' : 'O');
            }
        }
    } else if (mode == 3) {
        s.assign(n, 'X');
        int count = rnd.next(1, n);
        for (int i = 0; i < count; ++i) {
            s[rnd.next(0, n - 1)] = 'O';
        }
    } else if (mode == 4) {
        s.assign(n, 'O');
        int count = rnd.next(1, n);
        for (int i = 0; i < count; ++i) {
            s[rnd.next(0, n - 1)] = 'X';
        }
    } else if (mode == 5) {
        int split = rnd.next(0, n);
        s.assign(split, 'X');
        s += string(n - split, 'O');
    } else {
        double oProbability = rnd.next(0.05, 0.95);
        for (int i = 0; i < n; ++i) {
            s += (rnd.next() < oProbability ? 'O' : 'X');
        }
    }

    println(s);
    return 0;
}

#include "testlib.h"

#include <algorithm>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 40);
    string s(n, '.');

    if (mode == 0) {
        fill(s.begin(), s.end(), '.');
    } else if (mode == 1) {
        fill(s.begin(), s.end(), 'X');
    } else if (mode == 2) {
        char first = rnd.next(0, 1) ? '.' : 'X';
        for (int i = 0; i < n; ++i) {
            s[i] = (i % 2 == 0) ? first : (first == '.' ? 'X' : '.');
        }
    } else if (mode == 3) {
        char current = rnd.next(0, 1) ? '.' : 'X';
        for (int i = 0; i < n;) {
            int len = rnd.next(1, min(7, n - i));
            for (int j = 0; j < len; ++j) {
                s[i + j] = current;
            }
            i += len;
            current = (current == '.') ? 'X' : '.';
        }
    } else if (mode == 4) {
        double obstacleProbability = rnd.next(0.15, 0.85);
        for (int i = 0; i < n; ++i) {
            s[i] = rnd.next() < obstacleProbability ? 'X' : '.';
        }
    } else {
        int leftDots = rnd.next(0, min(8, n));
        int rightDots = rnd.next(0, min(8, n - leftDots));
        fill(s.begin(), s.end(), 'X');
        for (int i = 0; i < leftDots; ++i) {
            s[i] = '.';
        }
        for (int i = 0; i < rightDots; ++i) {
            s[n - 1 - i] = '.';
        }
        if (rnd.next(0, 1) && n >= 3) {
            int pos = rnd.next(1, n - 2);
            int len = rnd.next(1, min(5, n - pos));
            for (int i = 0; i < len; ++i) {
                s[pos + i] = '.';
            }
        }
    }

    int dots = (int)count(s.begin(), s.end(), '.');
    int m;
    if (dots == 0) {
        m = 0;
    } else {
        int choice = rnd.next(0, 3);
        if (choice == 0) {
            m = 0;
        } else if (choice == 1) {
            m = dots;
        } else {
            m = rnd.next(0, dots);
        }
    }

    println(n, m);
    println(s);
    return 0;
}

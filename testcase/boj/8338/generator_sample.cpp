#include "testlib.h"

#include <algorithm>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int m = rnd.next(1, 30);
    int n;
    string s;

    if (mode == 0) {
        n = rnd.next(1, 30);
        char c = rnd.next(0, 1) ? '1' : '0';
        s.assign(m, c);
    } else if (mode == 1) {
        n = rnd.next(1, 30);
        char first = rnd.next(0, 1) ? '1' : '0';
        for (int i = 0; i < m; ++i) {
            s += (i % 2 == 0) ? first : char('0' + '1' - first);
        }
    } else if (mode == 2) {
        n = rnd.next(1, 30);
        char c = rnd.next(0, 1) ? '1' : '0';
        while ((int)s.size() < m) {
            int len = min(rnd.next(1, 6), m - (int)s.size());
            s.append(len, c);
            c = (c == '0') ? '1' : '0';
        }
    } else if (mode == 3) {
        n = rnd.next(1, 8);
        m = rnd.next(1, 8);
        for (int i = 0; i < m; ++i) {
            s += rnd.next(0, 1) ? '1' : '0';
        }
    } else if (mode == 4) {
        n = rnd.next(31, 80);
        for (int i = 0; i < m; ++i) {
            s += rnd.next(0, 1) ? '1' : '0';
        }
    } else if (mode == 5) {
        m = rnd.next(20, 60);
        n = rnd.next(1, 60);
        for (int i = 0; i < m; ++i) {
            s += rnd.next(0, 3) == 0 ? '1' : '0';
        }
    } else {
        m = rnd.next(20, 60);
        n = rnd.next(1, 60);
        for (int i = 0; i < m; ++i) {
            s += rnd.next(0, 3) == 0 ? '0' : '1';
        }
    }

    println(m, n);
    println(s);
    return 0;
}

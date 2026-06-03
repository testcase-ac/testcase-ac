#include "testlib.h"
#include <algorithm>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    string s;

    if (mode == 0) {
        n = rnd.next(1, 12);
        s.assign(n, rnd.next(0, 1) ? '>' : '<');
    } else if (mode == 1) {
        n = rnd.next(1, 30);
        s.reserve(n);
        char first = rnd.next(0, 1) ? '>' : '<';
        for (int i = 0; i < n; ++i) {
            s.push_back((i % 2 == 0) ? first : (first == '>' ? '<' : '>'));
        }
    } else if (mode == 2) {
        int left = rnd.next(1, 12);
        int right = rnd.next(1, 12);
        int prefix = rnd.next(0, 6);
        int suffix = rnd.next(0, 6);
        n = prefix + left + right + suffix;
        s.reserve(n);
        for (int i = 0; i < prefix; ++i) s.push_back(rnd.next(0, 1) ? '>' : '<');
        s += string(left, '>');
        s += string(right, '<');
        for (int i = 0; i < suffix; ++i) s.push_back(rnd.next(0, 1) ? '>' : '<');
    } else if (mode == 3) {
        int blocks = rnd.next(2, 10);
        s.clear();
        char c = rnd.next(0, 1) ? '>' : '<';
        for (int i = 0; i < blocks; ++i) {
            int len = rnd.next(1, 8);
            s += string(len, c);
            c = (c == '>') ? '<' : '>';
        }
        n = (int)s.size();
    } else if (mode == 4) {
        n = rnd.next(1, 60);
        s.reserve(n);
        int percentGreater = rnd.next(5, 95);
        for (int i = 0; i < n; ++i) {
            s.push_back(rnd.next(1, 100) <= percentGreater ? '>' : '<');
        }
    } else {
        n = rnd.next(100, 2000);
        s.reserve(n);
        int period = rnd.next(2, 9);
        for (int i = 0; i < n; ++i) {
            bool flip = rnd.next(1, 100) <= 15;
            char c = ((i / period) % 2 == 0) ? '>' : '<';
            if (flip) c = (c == '>') ? '<' : '>';
            s.push_back(c);
        }
    }

    println(n);
    println(s);
    return 0;
}

#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 8);
    } else if (mode == 2) {
        n = rnd.next(9, 30);
    } else {
        n = rnd.next(31, 120);
    }

    string s;
    s.reserve(n);

    if (mode == 0) {
        s.push_back(rnd.next('a', 'z'));
    } else if (mode == 1) {
        char c = rnd.next('a', 'z');
        s.assign(n, c);
    } else if (mode == 2) {
        char lo = rnd.next('a', 'z');
        char hi = rnd.next(lo, 'z');
        for (int i = 0; i < n; ++i) {
            s.push_back(rnd.next(lo, hi));
        }
    } else if (mode == 3) {
        string pattern;
        int period = rnd.next(2, 5);
        for (int i = 0; i < period; ++i) {
            pattern.push_back(rnd.next('a', 'z'));
        }
        for (int i = 0; i < n; ++i) {
            s.push_back(pattern[i % period]);
        }
    } else {
        for (int i = 0; i < n; ++i) {
            s.push_back(rnd.next('a', 'z'));
        }
    }

    println(s);
    return 0;
}

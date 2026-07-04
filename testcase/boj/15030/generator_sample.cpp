#include "testlib.h"
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n;
    string s;

    if (mode == 0) {
        n = 1;
        s.push_back(char('a' + rnd.next(0, 25)));
    } else if (mode == 1) {
        n = rnd.next(2, 30);
        s.assign(n, char('a' + rnd.next(0, 25)));
    } else if (mode == 2) {
        n = rnd.next(2, 30);
        char a = char('a' + rnd.next(0, 24));
        char b = char(a + rnd.next(1, 'z' - a));
        for (int i = 0; i < n; ++i) s.push_back(rnd.next(0, 4) == 0 ? b : a);
        shuffle(s.begin(), s.end());
    } else if (mode == 3) {
        int blocks = rnd.next(2, 8);
        for (int i = blocks - 1; i >= 0; --i) {
            int count = rnd.next(1, 5);
            s.append(count, char('a' + i));
        }
    } else if (mode == 4) {
        n = rnd.next(3, 30);
        for (int i = 0; i < n; ++i) s.push_back(char('a' + i % 26));
        int swaps = rnd.next(1, min(8, n));
        for (int i = 0; i < swaps; ++i) {
            int x = rnd.next(0, n - 1);
            int y = rnd.next(0, n - 1);
            swap(s[x], s[y]);
        }
    } else if (mode == 5) {
        n = rnd.next(2, 30);
        int alphabet = rnd.next(2, 8);
        for (int i = 0; i < n; ++i) s.push_back(char('a' + rnd.next(0, alphabet - 1)));
    } else if (mode == 6) {
        n = rnd.next(26, 120);
        for (int i = 0; i < n; ++i) s.push_back(char('a' + i % 26));
        shuffle(s.begin(), s.end());
    } else {
        n = 1000;
        int alphabet = rnd.next(1, 26);
        for (int i = 0; i < n; ++i) s.push_back(char('a' + rnd.next(0, alphabet - 1)));
    }

    println(s);
    return 0;
}

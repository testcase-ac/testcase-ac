#include "testlib.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(1, 40);
    string s;
    s.reserve(n);

    if (mode == 0) {
        char c = char('0' + rnd.next(0, 1));
        s.assign(n, c);
    } else if (mode == 1) {
        char c = char('0' + rnd.next(0, 1));
        for (int i = 0; i < n; ++i) {
            s.push_back(c);
            c = (c == '0' ? '1' : '0');
        }
    } else if (mode == 2) {
        char base = char('0' + rnd.next(0, 1));
        s.assign(n, base);
        int flips = rnd.next(1, min(n, 6));
        for (int i = 0; i < flips; ++i) {
            int pos = rnd.next(0, n - 1);
            s[pos] = (s[pos] == '0' ? '1' : '0');
        }
    } else {
        char c = char('0' + rnd.next(0, 1));
        while ((int)s.size() < n) {
            int len = rnd.next(1, min(8, n - (int)s.size()));
            s.append(len, c);
            if (rnd.next(0, 99) < 75) c = (c == '0' ? '1' : '0');
        }
    }

    println(s);
    return 0;
}

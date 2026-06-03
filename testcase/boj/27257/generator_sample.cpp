#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int k;

    if (mode == 0) {
        int len = rnd.next(1, 9);
        string s;
        for (int i = 0; i < len; ++i) {
            s += char('1' + rnd.next(0, 8));
        }
        k = stoi(s);
    } else if (mode == 1) {
        int len = rnd.next(3, 9);
        string s;
        s += char('1' + rnd.next(0, 8));
        for (int i = 1; i + 1 < len; ++i) {
            s += rnd.next(0, 2) == 0 ? '0' : char('1' + rnd.next(0, 8));
        }
        s += char('1' + rnd.next(0, 8));
        k = stoi(s);
    } else if (mode == 2) {
        int len = rnd.next(2, 9);
        int tailZeros = rnd.next(1, len - 1);
        string s;
        for (int i = 0; i < len - tailZeros; ++i) {
            s += char('1' + rnd.next(0, 8));
        }
        s += string(tailZeros, '0');
        k = stoi(s);
    } else if (mode == 3) {
        int len = rnd.next(4, 9);
        string s;
        s += char('1' + rnd.next(0, 8));
        while ((int)s.size() < len) {
            int run = rnd.next(1, min(3, len - (int)s.size()));
            s += string(run, '0');
            if ((int)s.size() < len) {
                s += char('1' + rnd.next(0, 8));
            }
        }
        if (s.back() == '0') {
            s.back() = char('1' + rnd.next(0, 8));
        }
        k = stoi(s);
    } else {
        k = rnd.next(900000000, 1000000000);
    }

    println(k);
    return 0;
}

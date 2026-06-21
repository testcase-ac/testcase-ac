#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 2);
    } else if (mode == 1) {
        n = rnd.next(3, 12);
    } else {
        n = rnd.next(1, 60);
    }

    string s;
    s.reserve(n);

    if (mode == 0) {
        char bit = char('0' + rnd.next(0, 1));
        s.assign(n, bit);
    } else if (mode == 1) {
        char bit = char('0' + rnd.next(0, 1));
        for (int i = 0; i < n; ++i) s.push_back(char(bit ^ (i & 1)));
    } else if (mode == 2) {
        char bit = char('0' + rnd.next(0, 1));
        s.assign(n, bit);
    } else if (mode == 3) {
        char bit = char('0' + rnd.next(0, 1));
        while ((int)s.size() < n) {
            int remaining = n - (int)s.size();
            int run = rnd.next(1, min(remaining, rnd.next(2, 10)));
            s.append(run, bit);
            bit = char('0' + '1' - bit);
        }
    } else if (mode == 4) {
        double oneProbability = rnd.next(0.15, 0.85);
        for (int i = 0; i < n; ++i) {
            s.push_back(rnd.next() < oneProbability ? '1' : '0');
        }
    } else {
        char bit = char('0' + rnd.next(0, 1));
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 99) < 25) bit = char('0' + '1' - bit);
            s.push_back(bit);
        }
    }

    println(s);
    return 0;
}

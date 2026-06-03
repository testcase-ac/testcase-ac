#include "testlib.h"

#include <algorithm>
#include <string>

using namespace std;

char nonChicken() {
    return rnd.next(2) == 0 ? 'A' : rnd.next('D', 'Z');
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n = rnd.next(1, 30);
    string s(n, 'A');

    if (mode == 0) {
        fill(s.begin(), s.end(), 'C');
    } else if (mode == 1) {
        for (char& c : s) c = nonChicken();
    } else if (mode == 2) {
        int cCount = rnd.next(1, n);
        fill(s.begin(), s.begin() + cCount, 'C');
        for (int i = cCount; i < n; ++i) s[i] = nonChicken();
        shuffle(s.begin(), s.end());
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            s[i] = (i % 2 == rnd.next(2)) ? 'C' : nonChicken();
        }
    } else if (mode == 4) {
        int segments = rnd.next(1, min(n, 8));
        int pos = 0;
        for (int seg = 0; seg < segments; ++seg) {
            int remaining = n - pos;
            int len = (seg + 1 == segments) ? remaining : rnd.next(1, remaining - (segments - seg - 1));
            char ch = rnd.next(3) == 0 ? nonChicken() : 'C';
            for (int i = 0; i < len; ++i) s[pos + i] = ch;
            pos += len;
        }
    } else {
        int cPercent = rnd.next(0, 100);
        for (char& c : s) c = rnd.next(100) < cPercent ? 'C' : nonChicken();
    }

    println(n);
    println(s);

    return 0;
}

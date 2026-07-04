#include "testlib.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int a = 0, b = 0, c = 0;

    if (mode == 0) {
        a = rnd.next(1, 25);
    } else if (mode == 1) {
        b = rnd.next(1, 18);
    } else if (mode == 2) {
        c = rnd.next(1, 12);
    } else if (mode == 3) {
        a = rnd.next(0, 18);
        b = rnd.next(1, 18);
        c = rnd.next(0, 6);
    } else if (mode == 4) {
        a = rnd.next(0, 18);
        b = rnd.next(0, 8);
        c = rnd.next(1, 10);
    } else if (mode == 5) {
        int n = rnd.next(1, 30);
        a = rnd.next(0, n);
        b = rnd.next(0, n - a);
        c = n - a - b;
    } else if (mode == 6) {
        b = rnd.next(1, 14);
        c = rnd.next(1, 10);
    } else {
        int n = rnd.next(1, 40);
        a = rnd.wnext(n + 1, 2);
        b = rnd.next(0, n - a);
        c = n - a - b;
    }

    string s;
    s.append(a, 'A');
    s.append(b, 'B');
    s.append(c, 'C');
    shuffle(s.begin(), s.end());

    println(s);
    return 0;
}

#include "testlib.h"

#include <string>

using namespace std;

string randomDigits(int n, const string& alphabet) {
    string s;
    for (int i = 0; i < n; ++i) s += rnd.any(alphabet);
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(1, 30);
    string s;

    if (mode == 0) {
        n = rnd.next(1, 12);
        s = string(n, '0');
    } else if (mode == 1) {
        n = rnd.next(1, 20);
        s = randomDigits(n, "123456789");
    } else if (mode == 2) {
        n = rnd.next(2, 25);
        int prefix = rnd.next(1, n - 1);
        s = string(prefix, '0') + randomDigits(n - prefix, "123456789");
    } else if (mode == 3) {
        n = rnd.next(2, 25);
        int suffix = rnd.next(1, n - 1);
        s = randomDigits(n - suffix, "123456789") + string(suffix, '0');
    } else if (mode == 4) {
        n = rnd.next(3, 30);
        for (int i = 0; i < n; ++i) s += (i % 2 == 0 ? '0' : rnd.any(string("123456789")));
    } else if (mode == 5) {
        n = rnd.next(5, 30);
        s = randomDigits(n, "0011223456789");
    } else {
        n = rnd.next(1, 30);
        s = randomDigits(n, "0123456789");
    }

    int k;
    if (rnd.next(0, 4) == 0) {
        k = 1;
    } else if (rnd.next(0, 3) == 0) {
        k = n;
    } else {
        k = rnd.next(1, n);
    }

    println(n, k);
    println(s);

    return 0;
}

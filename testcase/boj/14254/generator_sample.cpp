#include "testlib.h"

#include <string>

using namespace std;

char randomLower() {
    return static_cast<char>('a' + rnd.next(26));
}

string randomString(int n, int alphabetSize) {
    string s;
    for (int i = 0; i < n; ++i) {
        s += static_cast<char>('a' + rnd.next(alphabetSize));
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n = 1;
    int k = 1;
    string password;

    if (mode == 0) {
        n = rnd.next(1, 6);
        k = rnd.next(1, n);
        password = randomString(n, rnd.next(1, 4));
    } else if (mode == 1) {
        n = rnd.next(7, 20);
        k = rnd.next(1, (n - 1) / 2);
        password = randomString(n, rnd.next(2, 8));
    } else if (mode == 2) {
        n = rnd.next(6, 25);
        k = rnd.next(n / 2 + 1, n - 1);
        password = randomString(n, rnd.next(2, 5));
    } else if (mode == 3) {
        n = rnd.next(2, 50);
        k = n;
        password = randomString(n, rnd.next(1, 6));
    } else if (mode == 4) {
        n = rnd.next(10, 50);
        k = rnd.next(1, n);
        password = randomString(n, 26);
    } else {
        n = rnd.next(8, 50);
        k = rnd.next(1, n);
        int period = rnd.next(1, 6);
        string base = randomString(period, rnd.next(2, 5));
        for (int i = 0; i < n; ++i) {
            char c = base[i % period];
            if (rnd.next(5) == 0) c = randomLower();
            password += c;
        }
    }

    println(password);
    println(k);

    return 0;
}

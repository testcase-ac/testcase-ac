#include "testlib.h"

#include <array>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long MAX_COUNT = 1000000000LL;
    array<long long, 6> a{};

    int mode = rnd.next(0, 5);
    if (mode == 0) {
        for (long long& x : a) x = rnd.next(0, 8);
    } else if (mode == 1) {
        long long base = rnd.next(0, 20);
        for (long long& x : a) x = max(0LL, base + rnd.next(-3, 3));
    } else if (mode == 2) {
        for (long long& x : a) x = rnd.next(0, 40);
        int scarceColor = rnd.next(0, 1);
        for (int i = scarceColor; i < 6; i += 2) a[i] = rnd.next(0, 2);
    } else if (mode == 3) {
        for (long long& x : a) x = rnd.next(0, 50);
        int abundantColor = rnd.next(0, 1);
        for (int i = abundantColor; i < 6; i += 2) a[i] = rnd.next(45, 80);
    } else if (mode == 4) {
        for (long long& x : a) x = rnd.next(0, 30);
        int idx = rnd.next(0, 5);
        a[idx] = MAX_COUNT - rnd.next(0, 10);
    } else {
        for (long long& x : a) {
            int choice = rnd.next(0, 3);
            if (choice == 0) x = 0;
            else if (choice == 1) x = rnd.next(1, 20);
            else if (choice == 2) x = rnd.next(1000, 1000000);
            else x = MAX_COUNT - rnd.next(0, 1000);
        }
    }

    println(a[0], a[1]);
    println(a[2], a[3]);
    println(a[4], a[5]);

    return 0;
}

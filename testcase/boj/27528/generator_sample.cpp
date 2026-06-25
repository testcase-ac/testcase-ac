#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n;
    if (mode == 0) n = rnd.next(1, 3);
    else if (mode == 5) n = rnd.next(9, 11);
    else n = rnd.next(2, 7);

    int roomCount = (1 << n) - 1;
    vector<long long> a(roomCount);

    if (mode == 0) {
        for (long long& x : a) x = rnd.next(-5, 5);
    } else if (mode == 1) {
        for (long long& x : a) x = rnd.next(-1000, 1000);
    } else if (mode == 2) {
        for (int i = 0; i < roomCount; ++i) {
            long long magnitude = rnd.next(0, 1000000000);
            a[i] = (i % 2 == 0 ? magnitude : -magnitude);
        }
    } else if (mode == 3) {
        long long cur = rnd.next(-100, 100);
        for (long long& x : a) {
            cur += rnd.next(-20, 80);
            x = cur;
        }
    } else if (mode == 4) {
        for (long long& x : a) {
            int pick = rnd.next(8);
            if (pick == 0) x = -1000000000LL;
            else if (pick == 1) x = 1000000000LL;
            else if (pick == 2) x = 0;
            else x = rnd.next(-1000000, 1000000);
        }
    } else {
        for (long long& x : a) x = rnd.next(-1000000000, 1000000000);
    }

    println(n);
    println(a);
    return 0;
}

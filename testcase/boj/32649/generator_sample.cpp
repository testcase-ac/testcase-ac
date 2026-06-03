#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int a = 1;
    int b = 2;
    int k = 2;

    if (mode == 0) {
        a = rnd.next(1, 30);
        int multiplier = rnd.next(2, 40);
        while (a * multiplier > 1000000) multiplier = rnd.next(2, 40);
        b = a * multiplier;
        k = rnd.next(2, 12);
    } else if (mode == 1) {
        a = rnd.next(1, 200);
        b = rnd.next(a + 1, min(1000000, a + 500));
        k = rnd.next(2, 20);
    } else if (mode == 2) {
        a = rnd.next(1, 100);
        vector<int> multipliers = {2, 3, 4, 6, 8, 12, 16, 24, 36, 48, 60, 72, 84, 96};
        vector<int> valid;
        for (int x : multipliers) {
            if (a * x <= 1000000) valid.push_back(x);
        }
        b = a * rnd.any(valid);
        k = rnd.next(2, 30);
    } else if (mode == 3) {
        a = rnd.next(1, 20);
        int bLimit = min(1000000, a * rnd.next(2, 1000));
        b = rnd.next(a + 1, bLimit);
        k = rnd.next(70, 100);
    } else if (mode == 4) {
        a = rnd.next(999000, 999999);
        b = rnd.next(a + 1, 1000000);
        k = rnd.next(2, 100);
    } else if (mode == 5) {
        a = rnd.next(1, 1000);
        b = 1000000;
        if (a >= b) a = 999999;
        k = rnd.next(2, 100);
    } else if (mode == 6) {
        a = rnd.next(1, 50);
        int multiplier = rnd.next(2, 1000000 / a);
        b = a * multiplier;
        k = rnd.next(2, 100);
    } else {
        a = rnd.next(1, 10);
        b = rnd.next(a + 1, 100);
        k = rnd.next(2, 6);
    }

    println(a, b, k);
    return 0;
}

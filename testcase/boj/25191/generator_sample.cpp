#include "testlib.h"

using namespace std;

int clampValue(int value) {
    return max(1, min(1000, value));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int a;
    int b;

    if (mode == 0) {
        n = rnd.next(1, 20);
        a = rnd.next(1, 20);
        b = rnd.next(1, 20);
    } else if (mode == 1) {
        n = rnd.next(1, 30);
        int drinks = rnd.next(1, 30);
        a = rnd.next(1, min(1000, drinks * 2 + 3));
        b = clampValue(drinks - a / 2);
    } else if (mode == 2) {
        n = rnd.next(1, 1000);
        a = rnd.next(1, 3);
        b = rnd.next(1, 3);
    } else if (mode == 3) {
        n = rnd.next(1, 10);
        a = rnd.next(900, 1000);
        b = rnd.next(900, 1000);
    } else if (mode == 4) {
        n = rnd.any(vector<int>{1, 2, 999, 1000});
        a = rnd.any(vector<int>{1, 2, 999, 1000});
        b = rnd.any(vector<int>{1, 2, 999, 1000});
    } else {
        int target = rnd.next(1, 1000);
        a = rnd.next(1, 1000);
        b = clampValue(target - a / 2 + rnd.next(-2, 2));
        n = clampValue(target + rnd.next(-2, 2));
    }

    println(n);
    println(a, b);
    return 0;
}

#include "testlib.h"
#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int a;
    int b;

    if (mode == 0) {
        a = rnd.next(-100, -1);
        b = rnd.next(1, 100);
    } else if (mode == 1) {
        a = rnd.next(1, 99);
        b = rnd.next(a + 1, 100);
    } else if (mode == 2) {
        vector<int> cold = {-100, -99, -2, -1};
        a = rnd.any(cold);
        b = rnd.next(1, min(100, rnd.next(1, 20)));
    } else if (mode == 3) {
        vector<int> warm = {1, 2, 50, 98, 99};
        a = rnd.any(warm);
        b = rnd.next(a + 1, 100);
    } else if (mode == 4) {
        a = rnd.next(-20, -1);
        b = rnd.next(80, 100);
    } else {
        a = rnd.next(1, 90);
        b = rnd.next(a + 1, min(100, a + rnd.next(1, 10)));
    }

    int c = rnd.next(1, 100);
    int d = rnd.next(1, 100);
    int e = rnd.next(1, 100);

    if (rnd.next(0, 4) == 0) c = rnd.any(vector<int>{1, 100});
    if (rnd.next(0, 4) == 0) d = rnd.any(vector<int>{1, 100});
    if (rnd.next(0, 4) == 0) e = rnd.any(vector<int>{1, 100});

    println(a);
    println(b);
    println(c);
    println(d);
    println(e);

    return 0;
}

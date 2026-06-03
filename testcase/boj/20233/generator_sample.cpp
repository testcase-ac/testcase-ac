#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int a = rnd.next(0, 100);
    int x = rnd.next(0, 100);
    int b = rnd.next(0, 100);
    int y = rnd.next(0, 100);
    int T = rnd.next(1, 1440);

    if (mode == 0) {
        T = rnd.any(vector<int>{1, 2, 29, 30});
    } else if (mode == 1) {
        T = rnd.any(vector<int>{31, 32, 44, 45});
    } else if (mode == 2) {
        T = rnd.any(vector<int>{46, 47, 100, 1440});
    } else if (mode == 3) {
        a = rnd.any(vector<int>{0, 100});
        x = rnd.any(vector<int>{0, 100});
        b = rnd.any(vector<int>{0, 100});
        y = rnd.any(vector<int>{0, 100});
        T = rnd.any(vector<int>{1, 30, 31, 45, 46, 1440});
    } else if (mode == 4) {
        x = rnd.next(0, 3);
        y = rnd.next(0, 3);
        T = rnd.next(25, 55);
    } else if (mode == 5) {
        a = rnd.next(0, 10);
        b = rnd.next(0, 10);
        x = rnd.next(90, 100);
        y = rnd.next(90, 100);
        T = rnd.next(35, 120);
    } else if (mode == 6) {
        a = rnd.next(90, 100);
        b = rnd.next(90, 100);
        x = rnd.next(0, 10);
        y = rnd.next(0, 10);
        T = rnd.next(35, 120);
    }

    println(a);
    println(x);
    println(b);
    println(y);
    println(T);

    return 0;
}

#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int MAXV = 5000000;
    int mode = rnd.next(0, 6);
    int n;
    int m;
    int a;

    if (mode == 0) {
        n = 1;
        m = rnd.next(1, 20);
        a = rnd.next(1, 20);
    } else if (mode == 1) {
        n = rnd.next(1, 12);
        m = 1;
        a = rnd.next(1, MAXV);
    } else if (mode == 2) {
        n = rnd.next(2, 30);
        m = rnd.next(2, 50);
        a = 1;
    } else if (mode == 3) {
        n = rnd.next(2, 30);
        m = rnd.next(2, 50);
        a = m;
    } else if (mode == 4) {
        n = rnd.next(1, 100);
        m = rnd.next(2, 500);
        a = rnd.next(1, 500);
    } else if (mode == 5) {
        n = rnd.next(MAXV - 1000, MAXV);
        m = rnd.next(2, 1000);
        a = rnd.next(1, MAXV);
    } else {
        vector<int> values = {1, 2, 3, 10, 100, 4999999, MAXV};
        n = rnd.any(values);
        m = rnd.any(values);
        a = rnd.any(values);
    }

    n = max(1, min(n, MAXV));
    m = max(1, min(m, MAXV));
    a = max(1, min(a, MAXV));

    int h = (m == 1 ? 0 : rnd.next(0, m - 1));
    println(n, m, a);
    println(h);

    return 0;
}

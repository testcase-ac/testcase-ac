#include "testlib.h"
#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>
using namespace std;

const int LIM = 1000000000;

int randomSign() {
    return rnd.next(0, 1) == 0 ? -1 : 1;
}

pair<int, int> withRandomSigns(int a, int b) {
    if (a != 0) a *= randomSign();
    if (b != 0) b *= randomSign();
    if (rnd.next(0, 1)) swap(a, b);
    return {a, b};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int m = 0;
    int n = 0;

    if (mode == 0) {
        m = 0;
        n = 0;
    } else if (mode == 1) {
        int a = rnd.next(1, 1000);
        int b = rnd.next(1, 1000);
        while (gcd(a, b) != 1) {
            a = rnd.next(1, 1000);
            b = rnd.next(1, 1000);
        }
        tie(m, n) = withRandomSigns(a, b);
    } else if (mode == 2) {
        int g = rnd.next(2, 1000);
        int a = rnd.next(1, LIM / g);
        int b = rnd.next(1, LIM / g);
        tie(m, n) = withRandomSigns(a * g, b * g);
    } else if (mode == 3) {
        int v = rnd.next(1, LIM);
        tie(m, n) = withRandomSigns(v, 0);
    } else if (mode == 4) {
        int v = rnd.next(1, LIM);
        tie(m, n) = withRandomSigns(v, v);
    } else if (mode == 5) {
        vector<int> candidates = {LIM, LIM - 1, LIM - 2, 999999937, 500000000, 1};
        m = rnd.any(candidates) * randomSign();
        n = rnd.any(candidates) * randomSign();
    } else if (mode == 6) {
        int base = rnd.next(1, 1000);
        int g = rnd.next(2, LIM / base);
        tie(m, n) = withRandomSigns(base * g, g);
    } else {
        m = rnd.next(-LIM, LIM);
        n = rnd.next(-LIM, LIM);
    }

    println(m, n);
    return 0;
}

#include "testlib.h"
#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 12);
    int mode = rnd.next(0, 4);
    vector<int> x(n), y(n), order(n), days(n);
    iota(x.begin(), x.end(), 1);
    iota(y.begin(), y.end(), 1);
    iota(order.begin(), order.end(), 0);
    iota(days.begin(), days.end(), 1);
    shuffle(y.begin(), y.end());
    shuffle(order.begin(), order.end());
    shuffle(days.begin(), days.end());

    println(n);
    for (int index : order) {
        int a;
        int b;
        if (mode == 1) {
            a = rnd.next(1, n);
            b = n;
        } else if (mode == 2) {
            a = 1;
            b = rnd.next(1, n);
        } else if (mode == 3) {
            a = b = days[index];
        } else if (mode == 4) {
            int center = rnd.next(1, n);
            a = rnd.next(1, center);
            b = rnd.next(center, n);
        } else {
            a = rnd.next(1, n);
            b = rnd.next(a, n);
        }
        println(x[index], y[index], a, b);
    }
}

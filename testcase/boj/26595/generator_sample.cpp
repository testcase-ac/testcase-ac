#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

const int MAX_N = 10000000;
const int MAX_POWER = 10000;
const int MAX_COST = 10000000;

int clampCost(int value) {
    return max(1, min(MAX_COST, value));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int a;
    int pa;
    int b;
    int pb;

    if (mode == 0) {
        n = rnd.next(1, 80);
        a = rnd.next(1, 40);
        b = rnd.next(1, 40);
        pa = rnd.next(1, 40);
        pb = rnd.next(1, 40);
    } else if (mode == 1) {
        n = rnd.next(20, 500);
        pa = rnd.next(1, 30);
        pb = rnd.next(1, 30);
        a = rnd.next(1, 200);
        b = rnd.next(1, 200);
        if (rnd.next(2) == 0) {
            a = rnd.next(1, 40) * pa;
            b = rnd.next(1, 40) * pb;
        }
    } else if (mode == 2) {
        int basePower = rnd.next(1, 60);
        int baseCost = rnd.next(1, 60);
        int scaleA = rnd.next(1, 8);
        int scaleB = rnd.next(1, 8);
        a = min(MAX_POWER, basePower * scaleA);
        b = min(MAX_POWER, basePower * scaleB);
        pa = clampCost(baseCost * scaleA + rnd.next(-1, 1));
        pb = clampCost(baseCost * scaleB + rnd.next(-1, 1));
        n = rnd.next(1, 300);
    } else if (mode == 3) {
        n = rnd.next(1, 200);
        a = rnd.next(1, MAX_POWER);
        b = rnd.next(1, MAX_POWER);
        pa = rnd.next(n + 1, MAX_COST);
        pb = rnd.next(1, n);
        if (rnd.next(2) == 0) {
            swap(a, b);
            swap(pa, pb);
        }
    } else if (mode == 4) {
        n = rnd.next(9000000, MAX_N);
        a = rnd.next(9000, MAX_POWER);
        b = rnd.next(9000, MAX_POWER);
        pa = rnd.next(1, 1000);
        pb = rnd.next(1, 1000);
    } else {
        n = rnd.next(1, MAX_N);
        vector<int> costs = {1, rnd.next(1, 10), rnd.next(10, 1000), rnd.next(1000, MAX_COST), MAX_COST};
        pa = rnd.any(costs);
        pb = rnd.any(costs);
        a = rnd.next(1, MAX_POWER);
        b = rnd.next(1, MAX_POWER);
    }

    println(n);
    println(a, pa, b, pb);
    return 0;
}

#include "testlib.h"

#include <algorithm>
#include <array>
#include <vector>

using namespace std;

array<int, 3> randomProbabilities() {
    int first = rnd.next(0, 100);
    int second = rnd.next(0, 100 - first);
    array<int, 3> p = {first, second, 100 - first - second};
    shuffle(p.begin(), p.end());
    return p;
}

array<int, 3> biasedProbabilities(int mode) {
    if (mode == 0) return {100, 0, 0};
    if (mode == 1) return {0, 100, 0};
    if (mode == 2) return {0, 0, 100};
    if (mode == 3) return {50, 0, 50};
    if (mode == 4) {
        int minus = rnd.next(70, 100);
        return {minus, 100 - minus, 0};
    }
    if (mode == 5) {
        int plus = rnd.next(70, 100);
        return {0, 100 - plus, plus};
    }
    return randomProbabilities();
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n;
    int h;

    if (mode == 0) {
        n = rnd.next(1, 12);
        h = 0;
    } else if (mode == 1) {
        n = rnd.next(1, 20);
        h = rnd.next(1, 4);
    } else if (mode == 2) {
        n = rnd.next(1, 30);
        h = 100;
    } else if (mode == 3) {
        n = rnd.next(50000, 100000);
        h = rnd.next(0, 100);
    } else {
        n = rnd.next(1, 200);
        h = rnd.next(0, 100);
    }

    int a;
    if (h == 0) {
        a = 0;
    } else if (mode == 1 || mode == 4) {
        a = rnd.any(vector<int>{0, h});
    } else {
        a = rnd.next(0, h);
    }

    array<int, 3> p = biasedProbabilities(rnd.next(0, 6));
    if (mode == 0) {
        p = randomProbabilities();
    }

    println(n, h, a, p[0], p[1], p[2]);
    return 0;
}

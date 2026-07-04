#include "testlib.h"
#include <algorithm>
#include <array>
using namespace std;

array<int, 3> splitTotal(int total) {
    int first = rnd.next(0, total);
    int second = rnd.next(0, total - first);
    array<int, 3> parts = {first, second, total - first - second};
    shuffle(parts.begin(), parts.end());
    return parts;
}

int clampNonNegative(int value) {
    return max(0, value);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int p3 = 0, p4 = 0, p0 = 0;

    if (mode == 0) {
        array<int, 3> parts = splitTotal(rnd.next(1, 24));
        p3 = parts[0];
        p4 = parts[1];
        p0 = parts[2];
    } else if (mode == 1) {
        p3 = rnd.next(0, 20) * 3 + rnd.next(0, 2);
        p4 = rnd.next(0, 20) * 4 + rnd.next(0, 3);
        p0 = rnd.next(0, 20);
    } else if (mode == 2) {
        int table3 = rnd.next(0, 8);
        int table4 = rnd.next(0, 8);
        p3 = table3 * 3 - rnd.next(0, min(2, table3 * 3));
        p4 = table4 * 4 - rnd.next(0, min(3, table4 * 4));
        p0 = table3 * 3 + table4 * 4 - p3 - p4 + rnd.next(0, 6);
    } else if (mode == 3) {
        int active = rnd.next(0, 2);
        if (active == 0) {
            p3 = rnd.next(1, 60);
            p4 = 0;
            p0 = rnd.next(0, 15);
        } else if (active == 1) {
            p3 = 0;
            p4 = rnd.next(1, 60);
            p0 = rnd.next(0, 15);
        } else {
            p3 = rnd.next(0, 30);
            p4 = rnd.next(0, 30);
            p0 = 0;
        }
    } else {
        int total = rnd.next(99950, 100000);
        array<int, 3> parts = splitTotal(total);
        p3 = parts[0];
        p4 = parts[1];
        p0 = parts[2];
    }

    p3 = clampNonNegative(p3);
    p4 = clampNonNegative(p4);
    p0 = clampNonNegative(p0);

    if (p3 + p4 + p0 == 0) {
        p0 = 1;
    }
    while (p3 + p4 + p0 > 100000) {
        if (p0 > 0) --p0;
        else if (p4 > 0) --p4;
        else --p3;
    }

    println(p3, p4, p0);
    return 0;
}

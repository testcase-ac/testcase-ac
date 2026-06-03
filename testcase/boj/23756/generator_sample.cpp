#include "testlib.h"
#include <vector>
using namespace std;

int norm(int x) {
    x %= 360;
    if (x < 0) x += 360;
    return x;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 25);
    if (rnd.next(0, 9) == 0) n = rnd.next(26, 100);

    int start = rnd.next(0, 359);
    int current = start;
    vector<int> angles;
    angles.reserve(n);

    if (mode == 0) {
        for (int i = 0; i < n; ++i) {
            current = norm(current + rnd.next(-20, 20));
            angles.push_back(current);
        }
    } else if (mode == 1) {
        vector<int> pool = {0, 1, 179, 180, 181, 358, 359};
        start = rnd.any(pool);
        for (int i = 0; i < n; ++i) angles.push_back(rnd.any(pool));
    } else if (mode == 2) {
        vector<int> steps = {179, 180, 181};
        for (int i = 0; i < n; ++i) {
            int step = rnd.any(steps);
            if (rnd.next(0, 1)) step = -step;
            current = norm(current + step);
            angles.push_back(current);
        }
    } else if (mode == 3) {
        int left = rnd.next(0, 20);
        int right = rnd.next(339, 359);
        for (int i = 0; i < n; ++i) {
            angles.push_back((i % 2 == 0) ? left : right);
            if (rnd.next(0, 2) == 0) left = rnd.next(0, 20);
            if (rnd.next(0, 2) == 0) right = rnd.next(339, 359);
        }
    } else if (mode == 4) {
        int value = rnd.next(0, 359);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 3) == 0) value = rnd.next(0, 359);
            angles.push_back(value);
        }
    } else {
        for (int i = 0; i < n; ++i) angles.push_back(rnd.next(0, 359));
    }

    println(n);
    println(start);
    for (int angle : angles) println(angle);

    return 0;
}

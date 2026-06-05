#include "testlib.h"

#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

long long tri(long long x) {
    return x * (x + 1) / 2;
}

int boundedK(long long value) {
    value = max(1LL, min(1000000000LL, value));
    return static_cast<int>(value);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 30);
    int k = 1;
    vector<int> xs;

    if (mode == 0) {
        k = rnd.next(1, 30);
        n = rnd.next(1, 12);
    } else if (mode == 1) {
        int speed = rnd.next(1, 45000);
        long long base = tri(speed);
        k = boundedK(base + rnd.next(-speed, speed));
        n = rnd.next(8, 25);
    } else if (mode == 2) {
        int speed = rnd.next(1, 31622);
        long long base = 1LL * speed * speed;
        k = boundedK(base + rnd.next(-speed, speed));
        n = rnd.next(8, 25);
    } else if (mode == 3) {
        k = rnd.next(900000000, 1000000000);
        n = rnd.next(12, 35);
    } else if (mode == 4) {
        k = rnd.any(vector<int>{1, 2, 3, 10, 1000000000});
        n = rnd.next(1, 20);
    } else {
        k = rnd.next(1, 1000000000);
        n = rnd.next(200, 1000);
    }

    int anchor = max(1, min(100000, static_cast<int>(rnd.next(1, 100000))));
    if (k <= 1000) {
        anchor = rnd.next(1, min(100000, max(1, k + 5)));
    } else if (mode == 1 || mode == 2) {
        anchor = rnd.next(1, min(100000, max(1, static_cast<int>(sqrt(k)) + 10)));
    }

    vector<int> special = {1, 2, 3, 4, 5, 99999, 100000, anchor};
    xs.reserve(n);
    while (static_cast<int>(xs.size()) < n) {
        int choice = rnd.next(0, 4);
        int x;
        if (choice == 0) {
            x = rnd.any(special);
        } else if (choice == 1) {
            int delta = rnd.next(-10, 10);
            x = anchor + delta;
        } else if (choice == 2) {
            int limit = max(1, min(100000, anchor * 2));
            x = rnd.next(1, limit);
        } else if (choice == 3) {
            x = rnd.next(99900, 100000);
        } else {
            x = rnd.next(1, 100000);
        }
        xs.push_back(max(1, min(100000, x)));
    }

    println(k, n);
    for (int x : xs) {
        println(x);
    }

    return 0;
}

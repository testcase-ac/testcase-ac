#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 4) {
        n = rnd.next(80, 100);
    } else if (mode == 5) {
        n = 1;
    } else {
        n = rnd.next(2, 12);
    }

    vector<pair<int, int>> items;
    long long sum = 0;

    for (int i = 0; i < n; ++i) {
        int a;
        int b;
        if (mode == 4) {
            a = rnd.next(900000, 1000000);
            b = 10;
        } else if (mode == 5) {
            a = rnd.next(1, 1000000);
            b = rnd.next(1, 10);
        } else {
            int priceMode = rnd.next(0, 3);
            if (priceMode == 0) {
                a = rnd.next(1, 20);
            } else if (priceMode == 1) {
                a = rnd.next(1000, 100000);
            } else {
                a = rnd.next(1, 1000000);
            }
            b = rnd.next(1, 10);
        }

        items.push_back({a, b});
        sum += 1LL * a * b;
    }

    long long x = sum;
    if (mode == 1 || mode == 3 || mode == 5) {
        long long delta = rnd.next(1, 1000);
        if (sum + delta <= 1000000000LL) {
            x = sum + delta;
        } else {
            x = max(1LL, sum - delta);
        }
        if (x == sum) {
            x = (sum == 1 ? 2 : sum - 1);
        }
    } else if (mode == 2) {
        x = rnd.next(1, 1000000000);
        if (x == sum) {
            x = (x == 1000000000LL ? x - 1 : x + 1);
        }
    }

    println(x);
    println(n);
    for (auto item : items) {
        println(item.first, item.second);
    }

    return 0;
}

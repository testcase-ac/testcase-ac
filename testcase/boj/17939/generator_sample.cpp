#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int clampPrice(int x) {
    return max(1, min(1000, x));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(2, 40);
    vector<int> price(n);

    if (mode == 0) {
        int cur = rnd.next(1, 80);
        for (int i = 0; i < n; i++) {
            cur += rnd.next(0, 30);
            price[i] = clampPrice(cur);
        }
    } else if (mode == 1) {
        int cur = rnd.next(650, 1000);
        for (int i = 0; i < n; i++) {
            cur -= rnd.next(0, 30);
            price[i] = clampPrice(cur);
        }
    } else if (mode == 2) {
        int low = rnd.next(1, 80);
        int high = rnd.next(850, 1000);
        for (int i = 0; i < n; i++) {
            if (i + 1 == n) {
                price[i] = high;
            } else if (rnd.next(0, 4) == 0) {
                price[i] = rnd.next(high - 80, high);
            } else {
                price[i] = rnd.next(low, min(200, low + 120));
            }
        }
    } else if (mode == 3) {
        int a = rnd.next(1, 1000);
        int b = rnd.next(1, 1000);
        int c = rnd.next(1, 1000);
        for (int i = 0; i < n; i++) {
            int block = (3 * i) / n;
            price[i] = block == 0 ? a : (block == 1 ? b : c);
        }
    } else if (mode == 4) {
        int cur = rnd.next(100, 900);
        for (int i = 0; i < n; i++) {
            cur += rnd.next(-120, 120);
            price[i] = clampPrice(cur);
        }
    } else if (mode == 5) {
        for (int i = 0; i < n; i++) {
            price[i] = (i % 2 == 0) ? rnd.next(1, 120) : rnd.next(850, 1000);
        }
    } else {
        n = rnd.next(35, 80);
        price.assign(n, 0);
        for (int i = 0; i < n; i++) {
            if (rnd.next(0, 9) == 0) {
                price[i] = rnd.next(1, 1000);
            } else {
                price[i] = rnd.next(350, 650);
            }
        }
    }

    println(n);
    println(price);
    return 0;
}

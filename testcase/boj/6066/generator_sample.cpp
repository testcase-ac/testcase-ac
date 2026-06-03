#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int h;
    vector<pair<int, int>> suppliers;

    if (mode == 0) {
        n = rnd.next(1, 8);
        h = rnd.next(1, 30);
        for (int i = 0; i < n; ++i) {
            int p = rnd.next(1, 12);
            int c = rnd.next(1, 20);
            suppliers.push_back({p, c});
        }
    } else if (mode == 1) {
        n = rnd.next(2, 12);
        h = rnd.next(20, 200);
        int cheap = rnd.next(2, 30);
        suppliers.push_back({cheap, 1});
        for (int i = 1; i < n; ++i) {
            int p = rnd.next(1, 60);
            int c = rnd.next(2, 80);
            suppliers.push_back({p, c});
        }
    } else if (mode == 2) {
        n = rnd.next(3, 15);
        h = rnd.next(100, 1000);
        int base = rnd.next(10, 80);
        for (int i = 0; i < n; ++i) {
            int p = max(1, base + rnd.next(-3, 3));
            int c = rnd.next(1, 120);
            suppliers.push_back({p, c});
        }
    } else if (mode == 3) {
        n = rnd.next(2, 10);
        h = rnd.next(500, 5000);
        for (int i = 0; i < n; ++i) {
            int p = rnd.next(4000, 5000);
            int c = rnd.next(1, 5000);
            suppliers.push_back({p, c});
        }
    } else if (mode == 4) {
        n = rnd.next(8, 25);
        h = rnd.next(1000, 10000);
        for (int i = 0; i < n; ++i) {
            int p = rnd.next(1, 5000);
            int c = rnd.next(1, 5000);
            suppliers.push_back({p, c});
        }
    } else {
        n = rnd.next(20, 100);
        h = rnd.next(10000, 50000);
        for (int i = 0; i < n; ++i) {
            int p = rnd.next(1, 5000);
            int c = rnd.next(1, 5000);
            suppliers.push_back({p, c});
        }
    }

    shuffle(suppliers.begin(), suppliers.end());

    println(n, h);
    for (auto supplier : suppliers) {
        println(supplier.first, supplier.second);
    }

    return 0;
}

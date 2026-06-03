#include "testlib.h"
#include <vector>
using namespace std;

int pickN(int mode) {
    if (mode == 0) return rnd.next(1, 12);
    if (mode == 1) return 6 * rnd.next(1, 16) + rnd.next(-1, 1);
    if (mode == 2) return rnd.any(vector<int>{1, 5, 6, 7, 99, 100});
    return rnd.next(1, 100);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = pickN(mode);
    int m = (mode == 3 ? rnd.next(20, 50) : rnd.next(1, 8));
    vector<pair<int, int>> brands;

    for (int i = 0; i < m; ++i) {
        int packagePrice;
        int singlePrice;

        if (mode == 0) {
            singlePrice = rnd.next(0, 20);
            packagePrice = rnd.next(0, 6 * singlePrice + 20);
        } else if (mode == 1) {
            packagePrice = rnd.next(0, 80);
            singlePrice = rnd.next(0, 25);
        } else if (mode == 2) {
            packagePrice = rnd.any(vector<int>{0, 1, 5, 6, 999, 1000});
            singlePrice = rnd.any(vector<int>{0, 1, 2, 166, 999, 1000});
        } else {
            packagePrice = rnd.next(0, 1000);
            singlePrice = rnd.next(0, 1000);
        }

        brands.push_back({packagePrice, singlePrice});
    }

    shuffle(brands.begin(), brands.end());

    println(n, m);
    for (auto [packagePrice, singlePrice] : brands) {
        println(packagePrice, singlePrice);
    }

    return 0;
}

#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct Ingredient {
    int x;
    int y;
    int smallSize;
    int smallPrice;
    int largeSize;
    int largePrice;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int m;

    if (mode == 0) {
        n = 1;
        m = rnd.next(1, 80);
    } else if (mode == 1) {
        n = rnd.next(2, 5);
        m = rnd.next(1, 40);
    } else if (mode == 2) {
        n = rnd.next(2, 8);
        m = rnd.next(60, 400);
    } else if (mode == 3) {
        n = rnd.next(4, 12);
        m = rnd.next(100, 1500);
    } else if (mode == 4) {
        n = rnd.next(1, 10);
        m = rnd.next(5000, 100000);
    } else {
        n = rnd.next(10, 20);
        m = rnd.next(20, 1000);
    }

    vector<Ingredient> ingredients;
    for (int i = 0; i < n; ++i) {
        Ingredient item;

        if (mode == 0) {
            item.x = rnd.next(90, 100);
            item.y = rnd.next(1, 20);
        } else if (mode == 5) {
            item.x = rnd.next(10, 30);
            item.y = rnd.next(70, 100);
        } else {
            item.x = rnd.next(10, 100);
            item.y = rnd.next(1, 100);
        }

        int family = rnd.next(0, 3);
        if (family == 0) {
            item.smallSize = rnd.next(1, 12);
            item.largeSize = rnd.next(item.smallSize + 1, min(100, item.smallSize + rnd.next(1, 15)));
        } else if (family == 1) {
            item.smallSize = rnd.next(30, 99);
            item.largeSize = rnd.next(item.smallSize + 1, 100);
        } else if (family == 2) {
            item.smallSize = rnd.next(1, 60);
            item.largeSize = rnd.next(item.smallSize + 1, 100);
        } else {
            item.smallSize = rnd.next(1, 99);
            item.largeSize = rnd.next(item.smallSize + 1, 100);
        }

        int priceGap;
        if (mode == 2) {
            item.smallPrice = rnd.next(10, 30);
            priceGap = rnd.next(1, 5);
        } else if (mode == 3) {
            item.smallPrice = rnd.next(70, 99);
            priceGap = rnd.next(1, 100 - item.smallPrice);
        } else {
            item.smallPrice = rnd.next(10, 99);
            priceGap = rnd.next(1, 100 - item.smallPrice);
        }
        item.largePrice = item.smallPrice + priceGap;

        ingredients.push_back(item);
    }

    shuffle(ingredients.begin(), ingredients.end());

    println(n, m);
    for (const Ingredient& item : ingredients) {
        println(item.x, item.y, item.smallSize, item.smallPrice, item.largeSize, item.largePrice);
    }

    return 0;
}

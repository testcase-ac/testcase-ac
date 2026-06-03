#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct Shop {
    int stock;
    int price;
    int orderFee;
};

int boundedPrice(int mode) {
    if (mode == 0) return rnd.next(0, 20);
    if (mode == 1) return rnd.any(vector<int>{0, 1, 2, 9999, 10000});
    return rnd.next(0, 10000);
}

int boundedFee(int mode) {
    if (mode == 0) return rnd.next(0, 200);
    if (mode == 1) return rnd.any(vector<int>{0, 1, 50, 999999, 1000000});
    return rnd.next(0, 1000000);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(4, 12);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(0, 5);
        int m = (mode == 5 ? rnd.next(20, 100) : rnd.next(1, 8));
        vector<Shop> shops;
        shops.reserve(m);

        int totalStock = 0;
        for (int i = 0; i < m; ++i) {
            int stock;
            if (mode == 0 && i == 0) {
                stock = 1;
            } else if (mode == 1 && i % 3 == 0) {
                stock = 0;
            } else if (mode == 5) {
                stock = rnd.next(0, 300);
            } else {
                stock = rnd.next(0, 30);
            }

            int price = boundedPrice(mode % 3);
            int orderFee = boundedFee((mode + i) % 3);
            shops.push_back({stock, price, orderFee});
            totalStock += stock;
        }

        if (totalStock == 0) {
            int pos = rnd.next(0, m - 1);
            shops[pos].stock = rnd.next(1, mode == 5 ? 300 : 30);
            totalStock += shops[pos].stock;
        }

        int n;
        int maxBuy = min(totalStock, 10000);
        if (mode == 0) {
            n = 1;
        } else if (mode == 2) {
            n = maxBuy;
        } else if (mode == 3) {
            n = max(1, maxBuy - rnd.next(0, min(maxBuy - 1, 5)));
        } else {
            n = rnd.next(1, maxBuy);
        }

        shuffle(shops.begin(), shops.end());

        println(n, m);
        for (const Shop& shop : shops) {
            println(shop.stock, shop.price, shop.orderFee);
        }
    }

    return 0;
}

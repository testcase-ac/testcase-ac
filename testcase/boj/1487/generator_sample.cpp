#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(1, 16);
    vector<pair<int, int>> buyers;

    if (mode == 0) {
        n = 1;
        int price = rnd.next(0, 1000000);
        int delivery = rnd.next(0, 1000000);
        buyers.push_back({price, delivery});
    } else if (mode == 1) {
        n = rnd.next(2, 12);
        for (int i = 0; i < n; ++i) {
            buyers.push_back({rnd.next(0, 80), 0});
        }
    } else if (mode == 2) {
        n = rnd.next(4, 16);
        int base = rnd.next(0, 200);
        for (int i = 0; i < n; ++i) {
            int price = base + rnd.next(0, 3) * rnd.next(0, 20);
            int delivery = rnd.next(0, min(price + 30, 1000000));
            buyers.push_back({price, delivery});
        }
    } else if (mode == 3) {
        n = rnd.next(3, 14);
        int pivot = rnd.next(1, 300);
        for (int i = 0; i < n; ++i) {
            int price = max(0, pivot + rnd.next(-25, 25));
            int delivery = max(0, pivot + rnd.next(-35, 35));
            buyers.push_back({price, delivery});
        }
    } else if (mode == 4) {
        n = rnd.next(2, 15);
        for (int i = 0; i < n; ++i) {
            int price = rnd.next(0, 150);
            int delivery = price + rnd.next(0, 150);
            buyers.push_back({price, min(delivery, 1000000)});
        }
    } else if (mode == 5) {
        n = rnd.next(5, 20);
        for (int i = 0; i < n; ++i) {
            int price = rnd.next(999900, 1000000);
            int delivery = rnd.next(999850, 1000000);
            buyers.push_back({price, delivery});
        }
    } else {
        n = rnd.next(10, 50);
        int priceHi = rnd.next(20, 1000);
        int deliveryHi = rnd.next(0, priceHi + 50);
        for (int i = 0; i < n; ++i) {
            buyers.push_back({rnd.next(0, priceHi), rnd.next(0, deliveryHi)});
        }
    }

    shuffle(buyers.begin(), buyers.end());

    println(n);
    for (auto [price, delivery] : buyers) {
        println(price, delivery);
    }

    return 0;
}

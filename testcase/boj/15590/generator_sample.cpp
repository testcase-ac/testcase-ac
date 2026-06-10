#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

static vector<int> makeCows(int n, int mode) {
    vector<int> cows;
    if (mode == 0) {
        int base = rnd.next(1, 12);
        for (int i = 0; i < n; ++i) cows.push_back(base + rnd.next(0, 4));
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) cows.push_back(rnd.next(1, 25));
        sort(cows.begin(), cows.end());
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            cows.push_back(i % 2 == 0 ? rnd.next(1, 5) : rnd.next(20, 60));
        }
    } else {
        for (int i = 0; i < n; ++i) cows.push_back(rnd.next(1, 1000000));
    }
    shuffle(cows.begin(), cows.end());
    return cows;
}

static vector<pair<int, int>> makeStores(int m, int mode) {
    vector<pair<int, int>> stores;
    for (int i = 0; i < m; ++i) {
        int quantity;
        int price;
        if (mode == 0) {
            quantity = rnd.next(1, 8);
            price = rnd.next(1, 30);
        } else if (mode == 1) {
            quantity = (i == 0 ? rnd.next(20, 80) : rnd.next(1, 6));
            price = rnd.next(1, 40);
        } else if (mode == 2) {
            quantity = rnd.next(1, 20);
            price = 50 - min(i * rnd.next(1, 5), 45);
        } else {
            quantity = rnd.next(1, 1000000);
            price = rnd.next(1, 1000000);
        }
        stores.push_back({quantity, price});
    }
    shuffle(stores.begin(), stores.end());
    return stores;
}

static vector<int> makeRentals(int r, int mode) {
    vector<int> rentals;
    for (int i = 0; i < r; ++i) {
        if (mode == 0) {
            rentals.push_back(rnd.next(1, 80));
        } else if (mode == 1) {
            rentals.push_back(i % 2 == 0 ? rnd.next(1, 20) : rnd.next(100, 300));
        } else if (mode == 2) {
            rentals.push_back(max(1, 200 - i * rnd.next(5, 25)));
        } else {
            rentals.push_back(rnd.next(1, 1000000));
        }
    }
    shuffle(rentals.begin(), rentals.end());
    return rentals;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(1, mode == 4 ? 20 : 10);
    int m = rnd.next(1, mode == 1 ? 4 : 10);
    int r = rnd.next(1, mode == 2 ? 20 : 10);

    if (mode == 3) {
        n = rnd.next(8, 18);
        m = rnd.next(1, 3);
        r = rnd.next(8, 18);
    } else if (mode == 4) {
        n = rnd.next(1, 20);
        m = rnd.next(1, 20);
        r = rnd.next(1, 20);
    }

    vector<int> cows = makeCows(n, mode);
    vector<pair<int, int>> stores = makeStores(m, mode);
    vector<int> rentals = makeRentals(r, mode);

    println(n, m, r);
    for (int cow : cows) println(cow);
    for (auto store : stores) println(store.first, store.second);
    for (int rental : rentals) println(rental);

    return 0;
}

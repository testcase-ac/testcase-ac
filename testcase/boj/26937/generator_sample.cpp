#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

struct Store {
    int postage;
    vector<pair<int, int>> items;
};

int priceForMode(int mode) {
    if (mode == 4 && rnd.next(0, 3) == 0) {
        return rnd.next(9000, 10000);
    }
    if (mode == 1 && rnd.next(0, 4) == 0) {
        return 1;
    }
    return rnd.next(1, 250);
}

int postageForMode(int mode) {
    if (mode == 1 || rnd.next(0, 5) == 0) {
        return 0;
    }
    if (mode == 4 && rnd.next(0, 2) == 0) {
        return rnd.next(9000, 10000);
    }
    return rnd.next(1, 300);
}

void addItem(Store& store, int book, int price) {
    for (auto [existingBook, _] : store.items) {
        if (existingBook == book) {
            return;
        }
    }
    store.items.push_back({book, price});
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n;
    int m;
    if (mode == 0) {
        n = 1;
        m = rnd.next(1, 3);
    } else if (mode == 1) {
        n = rnd.next(2, 8);
        m = rnd.next(1, 15);
    } else if (mode == 2) {
        n = rnd.next(3, 12);
        m = rnd.next(2, 8);
    } else if (mode == 3) {
        n = rnd.next(6, 18);
        m = rnd.next(4, 12);
    } else {
        n = rnd.next(8, 25);
        m = rnd.next(5, 15);
    }

    vector<Store> stores(m);
    for (Store& store : stores) {
        store.postage = postageForMode(mode);
    }

    vector<int> books(n);
    for (int book = 1; book <= n; ++book) {
        books[book - 1] = book;
    }
    shuffle(books.begin(), books.end());

    for (int book : books) {
        int storeIndex = rnd.next(0, m - 1);
        addItem(stores[storeIndex], book, priceForMode(mode));
    }

    double extraProbability;
    if (mode == 0) {
        extraProbability = 0.65;
    } else if (mode == 1) {
        extraProbability = 0.08;
    } else if (mode == 2) {
        extraProbability = 0.25;
    } else if (mode == 3) {
        extraProbability = 0.55;
    } else {
        extraProbability = 0.75;
    }

    for (int storeIndex = 0; storeIndex < m; ++storeIndex) {
        for (int book = 1; book <= n; ++book) {
            if (rnd.next() < extraProbability) {
                addItem(stores[storeIndex], book, priceForMode(mode));
            }
        }
        shuffle(stores[storeIndex].items.begin(), stores[storeIndex].items.end());
    }

    if (mode == 1 && m > 1) {
        vector<int> nonemptyStores;
        for (int storeIndex = 0; storeIndex < m; ++storeIndex) {
            if (!stores[storeIndex].items.empty()) {
                nonemptyStores.push_back(storeIndex);
            }
        }

        shuffle(nonemptyStores.begin(), nonemptyStores.end());
        int emptyStores = rnd.next(1, min((int)nonemptyStores.size(), min(m - 1, 4)));
        set<int> used(nonemptyStores.begin(), nonemptyStores.begin() + emptyStores);

        vector<pair<int, int>> removed;
        for (int storeIndex : used) {
            removed.insert(removed.end(), stores[storeIndex].items.begin(), stores[storeIndex].items.end());
            stores[storeIndex].items.clear();
        }
        for (auto [book, price] : removed) {
            int storeIndex = rnd.next(0, m - 1);
            while (used.count(storeIndex)) {
                storeIndex = rnd.next(0, m - 1);
            }
            addItem(stores[storeIndex], book, price);
        }
    }

    println(n, m);
    for (const Store& store : stores) {
        println((int)store.items.size(), store.postage);
        for (auto [book, price] : store.items) {
            println(book, price);
        }
    }

    return 0;
}

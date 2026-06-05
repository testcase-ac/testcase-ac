#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n, m;
    vector<pair<int, int>> items;
    vector<int> bags;

    if (mode == 0) {
        n = rnd.next(1, 4);
        m = rnd.next(1, 5);
        for (int i = 0; i < n; ++i) {
            int w = rnd.next(1, 12);
            int v = rnd.next(0, 25);
            items.push_back({w, v});
        }
        for (int i = 0; i < m; ++i) bags.push_back(rnd.next(1, 25));
    } else if (mode == 1) {
        n = rnd.next(4, 9);
        m = rnd.next(4, 8);
        int baseWeight = rnd.next(2, 8);
        for (int i = 0; i < n; ++i) {
            int w = baseWeight + rnd.next(0, 5);
            int v = max(0, w * rnd.next(1, 4) + rnd.next(-3, 3));
            items.push_back({w, min(v, 1000)});
        }
        for (int i = 0; i < m; ++i) bags.push_back(rnd.next(baseWeight, baseWeight * n + 12));
    } else if (mode == 2) {
        n = rnd.next(3, 8);
        m = rnd.next(3, 7);
        for (int i = 0; i < n; ++i) {
            int w = rnd.next(1, 20);
            int v = (i % 3 == 0) ? 0 : rnd.next(1, 40);
            items.push_back({w, v});
        }
        for (int i = 0; i < m; ++i) {
            if (i % 2 == 0)
                bags.push_back(rnd.next(1, 8));
            else
                bags.push_back(rnd.next(20, 80));
        }
    } else if (mode == 3) {
        n = rnd.next(6, 12);
        m = rnd.next(5, 10);
        int totalWeight = 0;
        for (int i = 0; i < n; ++i) {
            int w = rnd.next(1, 15);
            int v = rnd.next(1, 60);
            items.push_back({w, v});
            totalWeight += w;
        }
        for (int i = 0; i < m; ++i) {
            int choice = rnd.next(0, 2);
            if (choice == 0)
                bags.push_back(max(1, totalWeight + rnd.next(-5, 5)));
            else if (choice == 1)
                bags.push_back(rnd.any(items).first);
            else
                bags.push_back(rnd.next(1, totalWeight));
        }
    } else if (mode == 4) {
        n = rnd.next(2, 6);
        m = rnd.next(3, 8);
        for (int i = 0; i < n; ++i) {
            int w = rnd.next(50000, 100000);
            int v = rnd.next(0, 1000);
            items.push_back({w, v});
        }
        for (int i = 0; i < m; ++i) {
            if (i == 0)
                bags.push_back(rnd.next(1, 100));
            else if (i == 1)
                bags.push_back(rnd.next(90000, 110000));
            else
                bags.push_back(rnd.next(100000, 1000000));
        }
    } else {
        n = rnd.next(8, 18);
        m = rnd.next(6, 12);
        for (int i = 0; i < n; ++i) {
            int w = rnd.next(1, 40);
            int ratio = rnd.next(1, 8);
            int v = rnd.next(max(0, ratio * w - 10), min(1000, ratio * w + 10));
            items.push_back({w, v});
        }
        for (int i = 0; i < m; ++i) bags.push_back(rnd.next(1, 250));
    }

    shuffle(items.begin(), items.end());
    shuffle(bags.begin(), bags.end());

    println(n, m);
    for (const auto& item : items) println(item.first, item.second);
    for (int bag : bags) println(bag);

    return 0;
}

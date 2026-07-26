#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int sizeMode = rnd.next(0, 4);
    int n;
    if (sizeMode == 0) {
        n = 1;
    } else if (sizeMode == 1) {
        n = rnd.next(2, 4);
    } else if (sizeMode == 2) {
        n = rnd.next(5, 12);
    } else if (sizeMode == 3) {
        n = rnd.next(13, 30);
    } else {
        n = rnd.next(31, 80);
    }

    vector<int> cards;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        for (int x = 1; x <= n; ++x) {
            cards.push_back(x);
            cards.push_back(x);
        }
    } else if (mode == 1) {
        for (int x = 1; x <= n; ++x) {
            cards.push_back(x);
        }
        for (int x = n; x >= 1; --x) {
            cards.push_back(x);
        }
    } else if (mode == 2) {
        for (int x = 1; x <= n; ++x) {
            cards.push_back(x);
        }
        for (int x = 1; x <= n; ++x) {
            cards.push_back(x);
        }
    } else if (mode == 3) {
        for (int x = 1; x <= n; ++x) {
            cards.push_back(x);
            cards.push_back(x);
        }
        shuffle(cards.begin(), cards.end());
    } else if (mode == 4 && n >= 2) {
        int farValue = rnd.next(1, n);
        cards.push_back(farValue);
        vector<int> middle;
        for (int x = 1; x <= n; ++x) {
            if (x == farValue) {
                continue;
            }
            middle.push_back(x);
            middle.push_back(x);
        }
        shuffle(middle.begin(), middle.end());
        cards.insert(cards.end(), middle.begin(), middle.end());
        cards.push_back(farValue);
    } else {
        vector<int> order(n);
        iota(order.begin(), order.end(), 1);
        shuffle(order.begin(), order.end());
        int split = rnd.next(0, n);
        for (int i = 0; i < split; ++i) {
            cards.push_back(order[i]);
            cards.push_back(order[i]);
        }
        for (int i = split; i < n; ++i) {
            cards.push_back(order[i]);
        }
        for (int i = n - 1; i >= split; --i) {
            cards.push_back(order[i]);
        }
    }

    println(n);
    println(cards);
    return 0;
}

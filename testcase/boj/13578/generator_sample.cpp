#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

static void printCase(int n, int j, const vector<int>& cards) {
    println(n, j);
    println(cards);
}

static vector<int> randomCards(int n, int distinctValues) {
    vector<int> cards;
    cards.reserve(n);
    for (int i = 0; i < n; ++i) {
        cards.push_back(rnd.next(1, distinctValues));
    }
    return cards;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(5, 8);
    for (int tc = 0; tc < t; ++tc) {
        int mode = (tc + rnd.next(0, 5)) % 6;
        int j = rnd.next(2, 8);
        int n = rnd.next(j, 36);
        vector<int> cards;

        if (mode == 0) {
            n = max(n, j);
            int valueCount = min(13, max(2, n));
            for (int i = 0; i < n; ++i) {
                cards.push_back((i % valueCount) + 1);
            }
            shuffle(cards.begin(), cards.end());
        } else if (mode == 1) {
            n = rnd.next(max(2, j), 30);
            int a = rnd.next(1, 13);
            int b = rnd.next(1, 13);
            while (b == a) b = rnd.next(1, 13);
            for (int i = 0; i < n; ++i) {
                cards.push_back((i % 3 == 0) ? a : (i % 3 == 1 ? b : rnd.next(1, 13)));
            }
        } else if (mode == 2) {
            j = rnd.next(2, 6);
            n = rnd.next(j, 32);
            int base = rnd.next(1, 13);
            for (int i = 0; i < n; ++i) {
                if (i % 4 == 0 || i % 4 == 1) {
                    cards.push_back(base);
                } else {
                    cards.push_back(rnd.next(1, 13));
                }
            }
        } else if (mode == 3) {
            j = rnd.next(2, 10);
            n = rnd.next(j, 40);
            int distinctValues = rnd.next(2, 5);
            cards = randomCards(n, distinctValues);
        } else if (mode == 4) {
            j = rnd.next(2, 20);
            n = rnd.next(j, min(60, j + 25));
            int start = rnd.next(1, 13);
            for (int i = 0; i < n; ++i) {
                cards.push_back(((start + i - 1) % 13) + 1);
            }
        } else {
            j = rnd.next(2, 7);
            n = rnd.next(max(8, j), 45);
            int x = rnd.next(1, 13);
            int y = rnd.next(1, 13);
            while (y == x) y = rnd.next(1, 13);
            for (int i = 0; i < n; ++i) {
                if (i % 5 == 0) cards.push_back(x);
                else if (i % 5 == 1) cards.push_back(y);
                else if (i % 5 == 2) cards.push_back(x);
                else cards.push_back(rnd.next(1, 13));
            }
        }

        if (rnd.next(0, 1)) {
            shuffle(cards.begin(), cards.end());
        }

        printCase(n, j, cards);
    }

    println(0, 0);
    return 0;
}

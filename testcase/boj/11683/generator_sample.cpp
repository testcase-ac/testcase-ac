#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

vector<int> makePile(int n, int mode, int k) {
    vector<int> cards(n);

    if (mode == 0) {
        fill(cards.begin(), cards.end(), 1);
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) cards[i] = (i % 2) + 1;
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) cards[i] = min(10, i + 1);
    } else if (mode == 3) {
        int value = rnd.next(1, 10);
        fill(cards.begin(), cards.end(), value);
    } else if (mode == 4) {
        int limit = rnd.next(1, 10);
        for (int i = 0; i < n; ++i) cards[i] = rnd.next(1, limit);
    } else if (mode == 5) {
        for (int i = 0; i < n; ++i) {
            int distanceFromTop = n - i;
            cards[i] = rnd.next(1, min(10, max(1, distanceFromTop + k)));
        }
    } else {
        for (int i = 0; i < n; ++i) cards[i] = rnd.next(1, 10);
    }

    if (n >= 2 && rnd.next(4) == 0) {
        int suffix = rnd.next(1, min(n, k + 2));
        for (int i = n - suffix; i < n; ++i) cards[i] = rnd.next(1, 10);
    }

    return cards;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int p = rnd.next(1, 8);
    int k = rnd.next(1, 10);
    int sizeBias = rnd.next(4);

    println(p, k);
    for (int i = 0; i < p; ++i) {
        int n;
        if (sizeBias == 0) {
            n = rnd.next(1, 5);
        } else if (sizeBias == 1) {
            n = rnd.next(6, 15);
        } else {
            n = rnd.next(1, 30);
        }

        int mode = rnd.next(0, 6);
        vector<int> cards = makePile(n, mode, k);

        printf("%d", n);
        for (int card : cards) printf(" %d", card);
        printf("\n");
    }

    return 0;
}

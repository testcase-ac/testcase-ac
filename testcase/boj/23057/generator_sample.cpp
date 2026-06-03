#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 20);
    vector<long long> cards;

    if (mode == 0) {
        n = rnd.next(1, 8);
        int hi = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) cards.push_back(rnd.next(1, hi));
    } else if (mode == 1) {
        n = rnd.next(1, 20);
        long long value = rnd.next(1, 3);
        for (int i = 0; i < n; ++i) {
            cards.push_back(value);
            value = min(100000000LL, value * rnd.next(2, 3));
        }
    } else if (mode == 2) {
        n = rnd.next(12, 20);
        long long base = rnd.next(50000000, 100000000);
        for (int i = 0; i < n; ++i) cards.push_back(max(1LL, base - rnd.next(0, 1000)));
    } else if (mode == 3) {
        n = rnd.next(5, 20);
        int distinct = rnd.next(1, min(n, 5));
        vector<long long> pool;
        for (int i = 0; i < distinct; ++i) pool.push_back(rnd.next(1, 1000));
        for (int i = 0; i < n; ++i) cards.push_back(rnd.any(pool));
    } else if (mode == 4) {
        n = rnd.next(8, 20);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 3) == 0) {
                cards.push_back(rnd.next(1000000, 100000000));
            } else {
                cards.push_back(rnd.next(1, 200));
            }
        }
    } else {
        n = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) cards.push_back(rnd.next(1, 100000000));
    }

    shuffle(cards.begin(), cards.end());

    println(n);
    println(cards);

    return 0;
}

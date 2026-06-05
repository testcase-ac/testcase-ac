#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(7);
    int n = 1;
    int k = 1;

    if (mode == 0) {
        n = 1;
        k = rnd.next(1, 10);
    } else if (mode == 1) {
        n = rnd.next(2, 5);
        k = rnd.next(1, 3);
    } else if (mode == 2) {
        n = rnd.next(2, 10);
        k = 10;
    } else if (mode == 3) {
        n = rnd.next(20, 100);
        k = rnd.next(1, 4);
    } else if (mode == 4) {
        n = rnd.next(2, 20);
        k = rnd.next(5, 10);
    } else if (mode == 5) {
        n = rnd.next(2, 12);
        k = rnd.next(2, 8);
    } else {
        n = rnd.next(80, 100);
        k = 10;
    }

    vector<vector<int>> cards(n, vector<int>(k));

    if (mode == 4) {
        int value = rnd.next(1, 10);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < k; ++j) {
                cards[i][j] = value;
            }
        }
    } else if (mode == 5) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < k; ++j) {
                cards[i][j] = ((i + j + rnd.next(2)) % 2 == 0) ? 1 : 10;
            }
        }
    } else {
        int lo = 1;
        int hi = 10;
        if (mode == 0) {
            hi = rnd.next(1, 10);
        } else if (mode == 1 || mode == 3) {
            hi = rnd.next(2, 6);
        }

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < k; ++j) {
                if (mode == 6 && rnd.next(100) < 75) {
                    cards[i][j] = rnd.next(1, 3);
                } else {
                    cards[i][j] = rnd.next(lo, hi);
                }
            }
        }
    }

    println(n, k);
    for (int i = 0; i < n; ++i) {
        println(cards[i]);
    }

    return 0;
}

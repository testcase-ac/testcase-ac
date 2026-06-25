#include "testlib.h"

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

static vector<int> uniqueMoves(int k, int maxValue) {
    vector<int> pool;
    for (int x = 1; x <= maxValue; ++x) {
        pool.push_back(x);
    }
    shuffle(pool.begin(), pool.end());
    pool.resize(k);
    sort(pool.begin(), pool.end());
    return pool;
}

static vector<int> heapValues(int l, int mode, const vector<int>& moves) {
    vector<int> heaps;
    heaps.reserve(l);

    int smallMax = rnd.next(0, 30);
    int bigBase = rnd.next(9950, 10000);
    int chosenMove = rnd.any(moves);

    for (int i = 0; i < l; ++i) {
        if (mode == 0) {
            heaps.push_back(rnd.next(0, smallMax));
        } else if (mode == 1) {
            heaps.push_back(rnd.next(0, min(3, 10000 / chosenMove)) * chosenMove);
        } else if (mode == 2) {
            heaps.push_back(rnd.next(0, 1) ? rnd.next(0, 20) : rnd.next(bigBase, 10000));
        } else {
            heaps.push_back(rnd.next(0, 10000));
        }
    }

    return heaps;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int testCases = rnd.next(1, 4);
    for (int tc = 0; tc < testCases; ++tc) {
        int moveMode = rnd.next(0, 3);
        int k;
        int maxMove;
        if (moveMode == 0) {
            k = rnd.next(1, 4);
            maxMove = rnd.next(k, 8);
        } else if (moveMode == 1) {
            k = rnd.next(2, 8);
            maxMove = rnd.next(k, 30);
        } else if (moveMode == 2) {
            k = rnd.next(1, 6);
            maxMove = 10000;
        } else {
            k = rnd.next(8, 15);
            maxMove = rnd.next(k, 60);
        }

        vector<int> moves = uniqueMoves(k, maxMove);
        cout << k;
        for (int s : moves) {
            cout << ' ' << s;
        }
        cout << '\n';

        int m = rnd.next(1, 8);
        println(m);
        for (int i = 0; i < m; ++i) {
            int heapMode = rnd.next(0, 3);
            int l = rnd.next(1, heapMode == 3 ? 15 : 8);
            vector<int> heaps = heapValues(l, heapMode, moves);

            cout << l;
            for (int h : heaps) {
                cout << ' ' << h;
            }
            cout << '\n';
        }
    }

    println(0);
    return 0;
}

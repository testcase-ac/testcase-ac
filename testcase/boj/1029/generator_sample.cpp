#include "testlib.h"
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int N = 2;
    if (mode == 0) {
        N = rnd.next(2, 5);
    } else if (mode == 1) {
        N = rnd.next(6, 15);
    } else if (mode == 2) {
        N = rnd.next(4, 12);
    } else if (mode == 3) {
        N = rnd.next(5, 15);
    } else {
        N = rnd.next(2, 15);
    }

    vector<string> price(N, string(N, '0'));

    if (mode == 0) {
        int hi = rnd.next(1, 4);
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                price[i][j] = char('0' + rnd.next(0, hi));
            }
        }
    } else if (mode == 1) {
        vector<int> order(N);
        for (int i = 0; i < N; ++i) order[i] = i;
        shuffle(order.begin(), order.end());

        int current = rnd.next(0, 2);
        for (int idx = 0; idx + 1 < N; ++idx) {
            current = rnd.next(current, min(9, current + rnd.next(0, 2)));
            price[order[idx]][order[idx + 1]] = char('0' + current);
        }
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (price[i][j] == '0' && rnd.next(0, 99) < 35) {
                    price[i][j] = char('0' + rnd.next(0, 9));
                }
            }
        }
    } else if (mode == 2) {
        int low = rnd.next(0, 2);
        int high = rnd.next(6, 9);
        int gate = rnd.next(1, N - 1);
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                bool crossesGate = (i < gate && j >= gate) || (i >= gate && j < gate);
                int lo = crossesGate ? high : low;
                int hi = crossesGate ? 9 : min(5, low + 3);
                price[i][j] = char('0' + rnd.next(lo, hi));
            }
        }
    } else if (mode == 3) {
        int blocks = rnd.next(2, min(4, N));
        vector<int> group(N);
        for (int i = 0; i < N; ++i) group[i] = rnd.next(0, blocks - 1);
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                int base = abs(group[i] - group[j]) * rnd.next(1, 3);
                int noise = rnd.next(0, 3);
                price[i][j] = char('0' + min(9, base + noise));
            }
        }
    } else {
        int lo = rnd.next(0, 5);
        int hi = rnd.next(lo, 9);
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                price[i][j] = char('0' + rnd.next(lo, hi));
            }
        }
    }

    println(N);
    for (const string& row : price) {
        println(row);
    }

    return 0;
}

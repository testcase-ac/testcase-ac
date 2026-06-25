#include "testlib.h"
#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

static vector<int> identityOrder(int c) {
    vector<int> order(c);
    iota(order.begin(), order.end(), 0);
    return order;
}

static vector<int> winnerFirstOrder(int c, int winner) {
    vector<int> order;
    order.push_back(winner);
    for (int x = 0; x < c; ++x) {
        if (x != winner) {
            order.push_back(x);
        }
    }
    if (c > 2) {
        shuffle(order.begin() + 1, order.end());
    }
    return order;
}

static vector<int> rotatedOrder(int c, int start) {
    vector<int> order;
    for (int i = 0; i < c; ++i) {
        order.push_back((start + i) % c);
    }
    return order;
}

static vector<int> reversedOrder(int c) {
    vector<int> order = identityOrder(c);
    reverse(order.begin(), order.end());
    return order;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int caseCount = rnd.next(2, 5);
    for (int tc = 0; tc < caseCount; ++tc) {
        int mode = (tc == 0 ? 0 : rnd.next(0, 4));
        int b;
        int c;
        vector<vector<int>> ballots;

        if (mode == 0) {
            c = rnd.next(1, 8);
            b = rnd.next(1, 7);
            int winner = rnd.next(0, c - 1);
            for (int i = 0; i < b; ++i) {
                ballots.push_back(winnerFirstOrder(c, winner));
            }
        } else if (mode == 1) {
            c = 3;
            b = rnd.next(1, 3) * 3;
            for (int i = 0; i < b; ++i) {
                ballots.push_back(rotatedOrder(c, i % 3));
            }
        } else if (mode == 2) {
            c = rnd.next(2, 8);
            b = rnd.next(1, 4) * 2;
            vector<int> forward = identityOrder(c);
            vector<int> backward = reversedOrder(c);
            for (int i = 0; i < b; ++i) {
                ballots.push_back(i % 2 == 0 ? forward : backward);
            }
        } else {
            c = rnd.next(2, 9);
            b = rnd.next(1, 8);
            vector<int> base = identityOrder(c);
            for (int i = 0; i < b; ++i) {
                vector<int> order = base;
                shuffle(order.begin(), order.end());
                ballots.push_back(order);
            }
        }

        println(b, c);
        for (const vector<int>& ballot : ballots) {
            println(ballot);
        }
    }

    println(0, 0);
    return 0;
}

#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int W, H, K, T;

    if (mode == 0) {
        W = rnd.next(1, 5);
        H = rnd.next(1, 5);
        K = rnd.next(1, 8);
        T = rnd.next(0, 5);
    } else if (mode == 1) {
        W = rnd.next(1, 2) == 1 ? 1 : rnd.next(2, 20);
        H = W == 1 ? rnd.next(1, 20) : 1;
        K = rnd.next(1, 10);
        T = rnd.next(0, 25);
    } else if (mode == 2) {
        W = rnd.next(2, 30);
        H = rnd.next(2, 30);
        K = rnd.next(4, 14);
        T = rnd.next(0, 3);
    } else if (mode == 3) {
        W = rnd.next(1, 1000000);
        H = rnd.next(1, 1000000);
        K = rnd.next(1, 12);
        T = rnd.next(0, 1000000);
    } else if (mode == 4) {
        W = rnd.next(1, 50);
        H = rnd.next(1, 50);
        K = rnd.next(1, 16);
        T = 0;
    } else if (mode == 5) {
        W = rnd.next(1, 80);
        H = rnd.next(1, 80);
        K = rnd.next(1, 16);
        T = rnd.next(max(W, H), 1000000);
    } else {
        W = 1000000;
        H = 1000000;
        K = rnd.next(1, 12);
        T = rnd.next(0, 1000000);
    }

    vector<pair<int, int>> anchors = {
        {1, 1},
        {W, 1},
        {1, H},
        {W, H},
        {(W + 1) / 2, (H + 1) / 2},
        {rnd.next(1, W), rnd.next(1, H)}
    };

    println(W, H, K, T);
    for (int i = 0; i < K; ++i) {
        pair<int, int> point;
        if (mode == 2 && i < (int)anchors.size()) {
            point = anchors[i];
        } else if (rnd.next(0, 99) < 45) {
            point = rnd.any(anchors);
        } else {
            point = {rnd.next(1, W), rnd.next(1, H)};
        }
        println(point.first, point.second);
    }

    return 0;
}

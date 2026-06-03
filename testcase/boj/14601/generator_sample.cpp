#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int k;
    if (mode == 0) {
        k = 1;
    } else if (mode == 1) {
        k = 7;
    } else {
        k = rnd.next(1, 7);
    }

    int side = 1 << k;
    vector<pair<int, int>> candidates;

    if (mode == 0 || mode == 1) {
        candidates = {{1, 1}, {1, side}, {side, 1}, {side, side}};
    } else if (mode == 2) {
        int edge = rnd.next(0, 3);
        int pos = rnd.next(1, side);
        if (edge == 0) candidates.push_back({1, pos});
        if (edge == 1) candidates.push_back({side, pos});
        if (edge == 2) candidates.push_back({pos, 1});
        if (edge == 3) candidates.push_back({pos, side});
    } else if (mode == 3) {
        int mid = side / 2;
        for (int dx = -1; dx <= 2; ++dx) {
            for (int dy = -1; dy <= 2; ++dy) {
                int x = mid + dx;
                int y = mid + dy;
                if (1 <= x && x <= side && 1 <= y && y <= side) {
                    candidates.push_back({x, y});
                }
            }
        }
    } else if (mode == 4) {
        for (int base = 1; base < side; base *= 2) {
            candidates.push_back({base, base});
            candidates.push_back({base + 1, base});
            candidates.push_back({base, base + 1});
            candidates.push_back({base + 1, base + 1});
        }
    } else {
        int x = rnd.next(1, side);
        int y = rnd.next(1, side);
        candidates.push_back({x, y});
    }

    pair<int, int> drain = rnd.any(candidates);
    println(k);
    println(drain.first, drain.second);

    return 0;
}

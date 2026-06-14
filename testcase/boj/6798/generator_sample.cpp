#include "testlib.h"
#include <array>
#include <utility>
#include <vector>
using namespace std;

using Square = pair<int, int>;

bool inside(int x, int y) {
    return 1 <= x && x <= 8 && 1 <= y && y <= 8;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const vector<Square> corners = {{1, 1}, {1, 8}, {8, 1}, {8, 8}};
    const vector<Square> nearCorners = {{1, 2}, {2, 1}, {1, 7}, {2, 8},
                                        {7, 1}, {8, 2}, {7, 8}, {8, 7}};
    const array<pair<int, int>, 8> knightMoves = {{{1, 2}, {2, 1}, {2, -1}, {1, -2},
                                                   {-1, -2}, {-2, -1}, {-2, 1}, {-1, 2}}};

    Square start;
    Square target;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        start = {rnd.next(1, 8), rnd.next(1, 8)};
        target = start;
    } else if (mode == 1) {
        do {
            start = {rnd.next(1, 8), rnd.next(1, 8)};
            auto move = rnd.any(knightMoves);
            target = {start.first + move.first, start.second + move.second};
        } while (!inside(target.first, target.second));
    } else if (mode == 2) {
        start = rnd.any(corners);
        target = {rnd.next(1, 8), rnd.next(1, 8)};
    } else if (mode == 3) {
        start = rnd.any(nearCorners);
        target = rnd.any(nearCorners);
    } else {
        start = {rnd.next(1, 8), rnd.next(1, 8)};
        target = {rnd.next(1, 8), rnd.next(1, 8)};
    }

    println(start.first, start.second);
    println(target.first, target.second);
    return 0;
}

#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

struct Case {
    int r;
    int c;
    int rr;
    int cr;
    int rb;
    int cb;
};

pair<int, int> randomCell(int r, int c) {
    return {rnd.next(1, r), rnd.next(1, c)};
}

pair<int, int> differentCell(int r, int c, pair<int, int> first) {
    pair<int, int> second = randomCell(r, c);
    while (second == first) {
        second = randomCell(r, c);
    }
    return second;
}

Case makeCase(int mode) {
    int r = 1;
    int c = 1;
    pair<int, int> red;
    pair<int, int> blue;

    if (mode == 0) {
        if (rnd.next(2) == 0) {
            r = 1;
            c = rnd.next(2, 12);
        } else {
            r = rnd.next(2, 12);
            c = 1;
        }
        red = randomCell(r, c);
        blue = differentCell(r, c, red);
    } else if (mode == 1) {
        r = 2 * rnd.next(1, 4);
        c = 2 * rnd.next(1, 4);
        vector<pair<int, int>> corners = {{1, 1}, {1, c}, {r, 1}, {r, c}};
        shuffle(corners.begin(), corners.end());
        red = corners[0];
        blue = corners[1];
    } else if (mode == 2) {
        r = 2 * rnd.next(1, 4) + 1;
        c = rnd.next(2, 9);
        red = randomCell(r, c);
        blue = differentCell(r, c, red);
    } else if (mode == 3) {
        r = rnd.next(2, 9);
        c = 2 * rnd.next(1, 4) + 1;
        red = randomCell(r, c);
        blue = differentCell(r, c, red);
    } else if (mode == 4) {
        r = rnd.next(2, 8);
        c = rnd.next(2, 8);
        red = randomCell(r, c);
        vector<pair<int, int>> candidates;
        if (red.first > 1) candidates.push_back({red.first - 1, red.second});
        if (red.first < r) candidates.push_back({red.first + 1, red.second});
        if (red.second > 1) candidates.push_back({red.first, red.second - 1});
        if (red.second < c) candidates.push_back({red.first, red.second + 1});
        blue = rnd.any(candidates);
    } else if (mode == 5) {
        r = rnd.next(2, 10);
        c = rnd.next(2, 10);
        int row = rnd.next(1, r);
        red = {row, rnd.next(1, c)};
        blue = {row, rnd.next(1, c)};
        while (blue == red) {
            blue.second = rnd.next(1, c);
        }
    } else if (mode == 6) {
        r = rnd.next(2, 10);
        c = rnd.next(2, 10);
        int col = rnd.next(1, c);
        red = {rnd.next(1, r), col};
        blue = {rnd.next(1, r), col};
        while (blue == red) {
            blue.first = rnd.next(1, r);
        }
    } else {
        r = rnd.next(2, 10);
        c = rnd.next(2, 10);
        red = randomCell(r, c);
        blue = differentCell(r, c, red);
    }

    if (rnd.next(2) == 0) {
        swap(red, blue);
    }

    return {r, c, red.first, red.second, blue.first, blue.second};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(3, 8);
    vector<Case> cases;
    cases.reserve(t);

    for (int i = 0; i < t; ++i) {
        int mode = (i < 8) ? i : rnd.next(0, 7);
        cases.push_back(makeCase(mode));
    }
    shuffle(cases.begin(), cases.end());

    println(t);
    for (const Case& tc : cases) {
        printf("\n");
        println(tc.r, tc.c);
        println(tc.rr, tc.cr);
        println(tc.rb, tc.cb);
    }

    return 0;
}

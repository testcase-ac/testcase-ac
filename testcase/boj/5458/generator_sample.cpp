#include "testlib.h"

#include <algorithm>
#include <array>
#include <vector>
using namespace std;

struct Case {
    int s1;
    int s2;
    int s3;
    int f1;
    int f2;
    int f3;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<array<int, 3>> favoritePatterns = {
        {2, 1, 1}, {2, 1, 2}, {2, 3, 1}, {2, 3, 2},
        {3, 1, 1}, {3, 1, 2}, {3, 3, 1}, {3, 3, 2},
    };

    int t = rnd.next(8, 18);
    vector<Case> cases;
    cases.reserve(t);

    for (int i = 0; i < t; ++i) {
        int mode = rnd.next(0, 5);
        array<int, 3> stacks = {0, 0, 0};

        if (mode == 0) {
            int nonEmpty = rnd.next(0, 2);
            stacks[nonEmpty] = rnd.next(1, 20);
        } else if (mode == 1) {
            int empty = rnd.next(0, 2);
            for (int j = 0; j < 3; ++j) {
                if (j != empty) stacks[j] = rnd.next(1, 12);
            }
        } else if (mode == 2) {
            int base = rnd.next(1, 10);
            stacks = {base, base, base};
            stacks[rnd.next(0, 2)] = rnd.next(1, 20);
        } else if (mode == 3) {
            stacks = {rnd.next(15, 20), rnd.next(15, 20), rnd.next(15, 20)};
            if (rnd.next(0, 2) == 0) stacks[rnd.next(0, 2)] = 0;
        } else if (mode == 4) {
            int total = rnd.next(1, 20);
            for (int j = 0; j < total; ++j) {
                ++stacks[rnd.next(0, 2)];
            }
        } else {
            stacks = {rnd.next(0, 20), rnd.next(0, 20), rnd.next(0, 20)};
            if (stacks[0] + stacks[1] + stacks[2] == 0) {
                stacks[rnd.next(0, 2)] = rnd.next(1, 20);
            }
        }

        array<int, 3> favorites = favoritePatterns[rnd.next(0, static_cast<int>(favoritePatterns.size()) - 1)];
        cases.push_back({stacks[0], stacks[1], stacks[2], favorites[0], favorites[1], favorites[2]});
    }

    println(static_cast<int>(cases.size()));
    for (const Case& c : cases) {
        println(c.s1, c.s2, c.s3, c.f1, c.f2, c.f3);
    }

    return 0;
}

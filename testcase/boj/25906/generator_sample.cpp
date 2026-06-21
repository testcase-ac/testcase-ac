#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int T = 0;
    int K = 0;

    if (mode == 0) {
        T = rnd.next(0, 6);
        K = rnd.next(0, 6);
    } else if (mode == 1) {
        T = rnd.next(12, 45);
        K = rnd.next(0, 8);
    } else if (mode == 2) {
        T = rnd.next(25, 120);
        K = rnd.next(max(0, T - 15), T);
    } else if (mode == 3) {
        T = rnd.next(40, 150);
        K = rnd.next(1, 20);
    } else {
        T = rnd.next(0, 100000);
        K = rnd.next(0, 100000);
    }
    println(T, K);

    vector<int> maxLevel(5);
    for (int skill = 0; skill < 5; ++skill) {
        maxLevel[skill] = (mode == 4 ? rnd.next(1, 12) : rnd.next(1, 7));
        vector<int> attack(maxLevel[skill]);
        int value = rnd.next(1, 8);
        for (int level = 0; level < maxLevel[skill]; ++level) {
            if (level > 0) {
                int remaining = 100000 - value;
                if (!(mode == 3 && rnd.next(0, 2) == 0) && remaining > 0) {
                    value += rnd.next(0, min(remaining, mode == 4 ? 20000 : 12));
                }
            }
            attack[level] = value;
        }

        printf("%d", maxLevel[skill]);
        for (int value : attack) {
            printf(" %d", value);
        }
        printf("\n");
    }

    for (int kind = 0; kind < 3; ++kind) {
        int itemCount = (mode == 4 ? rnd.next(1, 12) : rnd.next(1, 7));
        println(itemCount);

        vector<int> costs(itemCount);
        for (int item = 0; item < itemCount; ++item) {
            if (mode == 0) {
                costs[item] = rnd.next(1, 20);
            } else if (mode == 1) {
                costs[item] = rnd.next(1, max(1, T / 2 + 5));
            } else if (mode == 2) {
                costs[item] = rnd.next(max(1, T / 2), min(100000, T + 20));
            } else if (mode == 3) {
                costs[item] = rnd.next(1, min(100000, T + 40));
            } else {
                costs[item] = rnd.next(1, 100000);
            }
        }
        println(costs);

        for (int item = 0; item < itemCount; ++item) {
            vector<int> levels(5, 0);
            int pattern = rnd.next(0, 4);
            if (pattern == 0) {
                int skill = rnd.next(0, 4);
                levels[skill] = rnd.next(0, maxLevel[skill]);
            } else if (pattern == 1) {
                int first = rnd.next(0, 4);
                int second = rnd.next(0, 4);
                levels[first] = rnd.next(0, maxLevel[first]);
                levels[second] = rnd.next(0, maxLevel[second]);
            } else if (pattern == 2) {
                for (int skill = 0; skill < 5; ++skill) {
                    levels[skill] = rnd.next(0, min(maxLevel[skill], 2));
                }
            } else if (pattern == 3) {
                int skill = rnd.next(0, 4);
                levels[skill] = maxLevel[skill];
            } else {
                for (int skill = 0; skill < 5; ++skill) {
                    levels[skill] = rnd.next(0, maxLevel[skill]);
                }
            }
            println(levels);
        }
    }

    return 0;
}

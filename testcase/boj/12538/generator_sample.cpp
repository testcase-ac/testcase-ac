#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

struct Rope {
    int length;
    char color;
};

int chooseLength(int mode) {
    if (mode == 0) {
        return rnd.next(1, 3);
    }
    if (mode == 1) {
        return rnd.next(95, 100);
    }
    if (mode == 2) {
        return rnd.any(vector<int>{1, 2, 99, 100});
    }
    return rnd.next(1, 100);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(6, 12);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(0, 5);
        int lengthMode = rnd.next(0, 3);
        int redCount = 0;
        int blueCount = 0;

        if (mode == 0) {
            redCount = rnd.next(1, 10);
        } else if (mode == 1) {
            blueCount = rnd.next(1, 10);
        } else if (mode == 2) {
            int k = rnd.next(1, 8);
            redCount = k;
            blueCount = k;
        } else if (mode == 3) {
            redCount = rnd.next(1, 3);
            blueCount = rnd.next(6, 12);
        } else if (mode == 4) {
            redCount = rnd.next(6, 12);
            blueCount = rnd.next(1, 3);
        } else {
            redCount = rnd.next(1, 10);
            blueCount = rnd.next(1, 10);
        }

        vector<Rope> ropes;
        for (int i = 0; i < redCount; ++i) {
            ropes.push_back({chooseLength(lengthMode), 'R'});
        }
        for (int i = 0; i < blueCount; ++i) {
            ropes.push_back({chooseLength(lengthMode), 'B'});
        }
        shuffle(ropes.begin(), ropes.end());

        println(static_cast<int>(ropes.size()));
        for (int i = 0; i < static_cast<int>(ropes.size()); ++i) {
            if (i > 0) {
                printf(" ");
            }
            printf("%d%c", ropes[i].length, ropes[i].color);
        }
        printf("\n");
    }

    return 0;
}

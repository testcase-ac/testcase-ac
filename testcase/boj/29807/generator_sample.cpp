#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int t = rnd.next(1, 5);
    vector<int> score(t);

    if (mode == 0) {
        for (int i = 0; i < t; ++i) {
            score[i] = rnd.next(0, 6);
        }
    } else if (mode == 1) {
        for (int i = 0; i < t; ++i) {
            score[i] = rnd.next(194, 200);
        }
    } else if (mode == 2) {
        int base = rnd.next(0, 200);
        for (int i = 0; i < t; ++i) {
            score[i] = base;
        }
    } else if (mode == 3) {
        for (int i = 0; i < t; ++i) {
            score[i] = (rnd.next(0, 1) == 0 ? 0 : 200);
        }
    } else if (mode == 4) {
        for (int i = 0; i < t; ++i) {
            score[i] = rnd.next(0, 200);
        }
        if (t >= 3 && rnd.next(0, 1) == 0) {
            score[2] = score[0];
        }
        if (t >= 4 && rnd.next(0, 1) == 0) {
            score[3] = score[1];
        }
    } else if (mode == 5) {
        t = rnd.next(1, 3);
        score.assign(t, 0);
        for (int i = 0; i < t; ++i) {
            score[i] = rnd.next(0, 200);
        }
    } else if (mode == 6) {
        t = rnd.next(4, 5);
        score.assign(t, 0);
        for (int i = 0; i < t; ++i) {
            score[i] = rnd.next(0, 200);
        }
        score[0] = rnd.next(0, 100);
        score[2] = rnd.next(score[0], 200);
        score[1] = rnd.next(0, 100);
        score[3] = rnd.next(score[1], 200);
    } else {
        t = rnd.next(4, 5);
        score.assign(t, 0);
        for (int i = 0; i < t; ++i) {
            score[i] = rnd.next(0, 200);
        }
        score[0] = rnd.next(100, 200);
        score[2] = rnd.next(0, score[0]);
        score[1] = rnd.next(100, 200);
        score[3] = rnd.next(0, score[1]);
    }

    println(t);
    println(score);

    return 0;
}

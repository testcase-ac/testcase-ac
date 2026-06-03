#include "testlib.h"

#include <vector>
using namespace std;

int evenInRange(int lo, int hi) {
    return 2 * rnd.next(lo / 2, hi / 2);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int m;
    vector<vector<int>> progress(2, vector<int>(3));

    if (mode == 0) {
        n = rnd.next(1, 3);
        m = rnd.next(1, 8);
        for (int mission = 0; mission < 2; ++mission) {
            for (int place = 0; place < 3; ++place) {
                progress[mission][place] = evenInRange(0, 4);
            }
        }
    } else if (mode == 1) {
        n = rnd.next(6, 8);
        m = rnd.next(18, 25);
        for (int mission = 0; mission < 2; ++mission) {
            for (int place = 0; place < 3; ++place) {
                progress[mission][place] = evenInRange(6, 10);
            }
        }
    } else if (mode == 2) {
        n = rnd.next(2, 8);
        m = rnd.next(1, 25);
        int mainPlace = rnd.next(0, 2);
        for (int mission = 0; mission < 2; ++mission) {
            for (int place = 0; place < 3; ++place) {
                progress[mission][place] = (place == mainPlace) ? evenInRange(8, 10) : evenInRange(0, 4);
            }
        }
    } else if (mode == 3) {
        n = rnd.next(1, 8);
        m = rnd.next(1, 25);
        for (int mission = 0; mission < 2; ++mission) {
            for (int place = 0; place < 3; ++place) {
                progress[mission][place] = rnd.next(0, 5) * 2;
            }
        }
    } else {
        n = rnd.next(4, 8);
        int daily = evenInRange(2, 8);
        m = rnd.next(1, 25);
        for (int mission = 0; mission < 2; ++mission) {
            for (int place = 0; place < 3; ++place) {
                int delta = rnd.next(-1, 1) * 2;
                int value = daily + delta;
                if (value < 0) value = 0;
                if (value > 10) value = 10;
                progress[mission][place] = value;
            }
        }
    }

    println(n, m);
    for (int mission = 0; mission < 2; ++mission) {
        println(progress[mission]);
    }

    return 0;
}

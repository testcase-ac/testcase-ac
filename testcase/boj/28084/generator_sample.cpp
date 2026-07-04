#include "testlib.h"
#include <vector>
using namespace std;

int evenProgress(int loIndex, int hiIndex) {
    return 2 * rnd.next(loIndex, hiIndex);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int nMode = rnd.next(0, 4);
    long long n;
    if (nMode == 0) {
        n = 1;
    } else if (nMode == 1) {
        n = rnd.next(2, 8);
    } else if (nMode == 2) {
        n = rnd.next(9LL, 1000LL);
    } else if (nMode == 3) {
        n = rnd.next(1000000LL, 1000000000LL);
    } else {
        n = rnd.next(999999999000LL, 1000000000000LL);
    }

    int mMode = rnd.next(0, 4);
    int m;
    if (mMode == 0) {
        m = 1;
    } else if (mMode == 1) {
        m = 25;
    } else if (mMode == 2) {
        m = rnd.next(2, 10);
    } else if (mMode == 3) {
        m = rnd.next(11, 24);
    } else {
        m = rnd.next(1, 25);
    }

    vector<vector<int>> progress(2, vector<int>(3));
    int pMode = rnd.next(0, 5);
    if (pMode == 0) {
        for (int mission = 0; mission < 2; ++mission) {
            for (int place = 0; place < 3; ++place) {
                progress[mission][place] = evenProgress(0, 5);
            }
        }
    } else if (pMode == 1) {
        for (int mission = 0; mission < 2; ++mission) {
            for (int place = 0; place < 3; ++place) {
                progress[mission][place] = evenProgress(0, 2);
            }
        }
    } else if (pMode == 2) {
        for (int mission = 0; mission < 2; ++mission) {
            for (int place = 0; place < 3; ++place) {
                progress[mission][place] = evenProgress(3, 5);
            }
        }
    } else if (pMode == 3) {
        int strongPlace = rnd.next(0, 2);
        for (int mission = 0; mission < 2; ++mission) {
            for (int place = 0; place < 3; ++place) {
                progress[mission][place] = (place == strongPlace)
                    ? evenProgress(4, 5)
                    : evenProgress(0, 2);
            }
        }
    } else if (pMode == 4) {
        int strongMission = rnd.next(0, 1);
        for (int mission = 0; mission < 2; ++mission) {
            for (int place = 0; place < 3; ++place) {
                progress[mission][place] = (mission == strongMission)
                    ? evenProgress(3, 5)
                    : evenProgress(0, 3);
            }
        }
    } else {
        int value = evenProgress(0, 5);
        for (int mission = 0; mission < 2; ++mission) {
            for (int place = 0; place < 3; ++place) {
                progress[mission][place] = value;
            }
        }
    }

    println(n, m);
    println(progress[0]);
    println(progress[1]);

    return 0;
}

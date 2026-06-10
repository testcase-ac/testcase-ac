#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 35);
    string breeds(n, 'G');

    if (mode == 0) {
        int split = rnd.next(1, n - 1);
        for (int i = split; i < n; ++i) {
            breeds[i] = 'H';
        }
    } else if (mode == 1) {
        int split = rnd.next(1, n - 1);
        for (int i = 0; i < split; ++i) {
            breeds[i] = 'H';
        }
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            breeds[i] = (i % 2 == 0 ? 'G' : 'H');
        }
        if (rnd.next(0, 1)) {
            for (char& breed : breeds) {
                breed = (breed == 'G' ? 'H' : 'G');
            }
        }
    } else if (mode == 3) {
        int gPos = rnd.next(0, n - 1);
        fill(breeds.begin(), breeds.end(), 'H');
        breeds[gPos] = 'G';
        for (int i = 0; i < n; ++i) {
            if (i != gPos && rnd.next(0, 4) == 0) {
                breeds[i] = 'G';
            }
        }
    } else if (mode == 4) {
        int hPos = rnd.next(0, n - 1);
        fill(breeds.begin(), breeds.end(), 'G');
        breeds[hPos] = 'H';
        for (int i = 0; i < n; ++i) {
            if (i != hPos && rnd.next(0, 4) == 0) {
                breeds[i] = 'H';
            }
        }
    } else {
        bool hasG = false;
        bool hasH = false;
        for (int i = 0; i < n; ++i) {
            breeds[i] = rnd.next(0, 1) ? 'G' : 'H';
            hasG = hasG || breeds[i] == 'G';
            hasH = hasH || breeds[i] == 'H';
        }
        if (!hasG) {
            breeds[rnd.next(0, n - 1)] = 'G';
        }
        if (!hasH) {
            breeds[rnd.next(0, n - 1)] = 'H';
        }
    }

    int firstG = -1;
    int lastG = -1;
    int firstH = -1;
    int lastH = -1;
    for (int i = 0; i < n; ++i) {
        if (breeds[i] == 'G') {
            if (firstG == -1) {
                firstG = i;
            }
            lastG = i;
        } else {
            if (firstH == -1) {
                firstH = i;
            }
            lastH = i;
        }
    }

    vector<int> e(n);
    for (int i = 0; i < n; ++i) {
        int reachBias = rnd.next(-2, 2);
        if (reachBias < 0) {
            e[i] = i + 1;
        } else if (reachBias == 0) {
            e[i] = rnd.next(i + 1, n);
        } else {
            e[i] = max(i + 1, n - rnd.next(0, min(4, n - i - 1)));
        }
    }

    e[firstG] = max(e[firstG], lastG + 1);
    e[firstH] = max(e[firstH], lastH + 1);

    println(n);
    println(breeds);
    println(e);
}

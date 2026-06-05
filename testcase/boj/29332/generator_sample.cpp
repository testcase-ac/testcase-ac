#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

struct Clue {
    long long x;
    long long y;
    char d;
};

long long pickOutsideLow(long long lo) {
    long long gap = rnd.next(1, 8);
    return max(-1000000000LL, lo - gap);
}

long long pickOutsideHigh(long long hi) {
    long long gap = rnd.next(1, 8);
    return min(1000000000LL, hi + gap);
}

long long pickCoord() {
    if (rnd.next(10) == 0) {
        return rnd.any(vector<long long>{-1000000000LL, -999999999LL, 999999999LL, 1000000000LL});
    }
    return rnd.next(-20, 20);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    long long loX = rnd.next(-8, 4);
    long long hiX = rnd.next(loX, loX + rnd.next(0, 8));
    long long loY = rnd.next(-8, 4);
    long long hiY = rnd.next(loY, loY + rnd.next(0, 8));

    vector<char> dirs;
    if (mode == 0) {
        dirs = {'L', 'R', 'U', 'D'};
    } else if (mode == 1) {
        dirs = {'L', 'R'};
    } else if (mode == 2) {
        dirs = {'U', 'D'};
    } else if (mode == 3) {
        dirs = {rnd.any(string("LRUD"))};
    } else {
        loX = rnd.any(vector<long long>{-999999990LL, -999999980LL, 999999980LL});
        hiX = min(1000000000LL, loX + rnd.next(0, 5));
        loY = rnd.any(vector<long long>{-999999990LL, -999999980LL, 999999980LL});
        hiY = min(1000000000LL, loY + rnd.next(0, 5));
        dirs = {'L', 'R', 'U', 'D'};
    }

    int n = rnd.next((int)dirs.size(), 20);
    vector<Clue> clues;
    for (char d : dirs) {
        if (d == 'L') clues.push_back({pickOutsideHigh(hiX), pickCoord(), d});
        if (d == 'R') clues.push_back({pickOutsideLow(loX), pickCoord(), d});
        if (d == 'U') clues.push_back({pickCoord(), pickOutsideLow(loY), d});
        if (d == 'D') clues.push_back({pickCoord(), pickOutsideHigh(hiY), d});
    }

    while ((int)clues.size() < n) {
        char d = rnd.any(dirs);
        if (d == 'L') clues.push_back({pickOutsideHigh(hiX), pickCoord(), d});
        if (d == 'R') clues.push_back({pickOutsideLow(loX), pickCoord(), d});
        if (d == 'U') clues.push_back({pickCoord(), pickOutsideLow(loY), d});
        if (d == 'D') clues.push_back({pickCoord(), pickOutsideHigh(hiY), d});
    }

    shuffle(clues.begin(), clues.end());

    println((int)clues.size());
    for (const Clue& clue : clues) {
        println(clue.x, clue.y, string(1, clue.d));
    }

    return 0;
}

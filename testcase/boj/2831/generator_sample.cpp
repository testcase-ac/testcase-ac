#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int signedHeight(int height, bool wantsTaller) {
    return wantsTaller ? height : -height;
}

int randomHeight() {
    return rnd.next(1500, 2500);
}

int boundaryBiasedHeight() {
    vector<int> candidates = {1500, 1501, 1700, 1800, 1900, 2499, 2500};
    return rnd.any(candidates);
}

void addPairPattern(vector<int>& men, vector<int>& women, int mode) {
    int low = rnd.next(1500, 2100);
    int high = rnd.next(low + 1, 2500);

    if (mode == 0) {
        men.push_back(signedHeight(high, false));
        women.push_back(signedHeight(low, true));
    } else if (mode == 1) {
        men.push_back(signedHeight(low, true));
        women.push_back(signedHeight(high, false));
    } else if (mode == 2) {
        int h = boundaryBiasedHeight();
        men.push_back(signedHeight(h, rnd.next(0, 1)));
        women.push_back(signedHeight(h, rnd.next(0, 1)));
    } else {
        men.push_back(signedHeight(boundaryBiasedHeight(), rnd.next(0, 1)));
        women.push_back(signedHeight(boundaryBiasedHeight(), rnd.next(0, 1)));
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = mode == 5 ? rnd.next(30, 80) : rnd.next(1, 24);

    vector<int> men;
    vector<int> women;
    men.reserve(n);
    women.reserve(n);

    for (int i = 0; i < n; ++i) {
        if (mode == 0) {
            addPairPattern(men, women, rnd.next(0, 1));
        } else if (mode == 1) {
            addPairPattern(men, women, 0);
        } else if (mode == 2) {
            addPairPattern(men, women, 1);
        } else if (mode == 3) {
            addPairPattern(men, women, 2);
        } else if (mode == 4) {
            men.push_back(signedHeight(randomHeight(), rnd.next(0, 1)));
            women.push_back(signedHeight(randomHeight(), rnd.next(0, 1)));
        } else {
            addPairPattern(men, women, rnd.wnext(4, -1));
        }
    }

    shuffle(men.begin(), men.end());
    shuffle(women.begin(), women.end());

    println(n);
    println(men);
    println(women);

    return 0;
}

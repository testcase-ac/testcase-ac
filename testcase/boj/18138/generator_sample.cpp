#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int clampWidth(int x) {
    return max(1, min(1000, x));
}

bool fits(int shirt, int collar) {
    return (shirt <= collar * 2 && 4 * collar <= shirt * 3) ||
           (shirt <= collar && 4 * collar <= shirt * 5);
}

int compatibleCollar(int shirt) {
    vector<int> candidates;

    for (int delta = -2; delta <= 2; ++delta) {
        candidates.push_back(clampWidth((shirt + 1) / 2 + delta));
        candidates.push_back(clampWidth((3 * shirt) / 4 + delta));
        candidates.push_back(clampWidth(shirt + delta));
        candidates.push_back(clampWidth((5 * shirt) / 4 + delta));
    }

    vector<int> valid;
    for (int collar : candidates) {
        if (fits(shirt, collar)) valid.push_back(collar);
    }

    return rnd.any(valid);
}

int incompatibleCollar(int shirt) {
    vector<int> candidates;

    for (int delta = -3; delta <= 3; ++delta) {
        candidates.push_back(clampWidth(shirt / 2 + delta));
        candidates.push_back(clampWidth((3 * shirt) / 4 + 1 + delta));
        candidates.push_back(clampWidth(shirt - 1 + delta));
        candidates.push_back(clampWidth((5 * shirt) / 4 + 1 + delta));
    }
    candidates.push_back(1);
    candidates.push_back(1000);

    vector<int> invalid;
    for (int collar : candidates) {
        if (!fits(shirt, collar)) invalid.push_back(collar);
    }

    if (!invalid.empty()) return rnd.any(invalid);

    int collar = rnd.next(1, 1000);
    while (fits(shirt, collar)) collar = rnd.next(1, 1000);
    return collar;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(1, 25);
    int m = rnd.next(1, 25);

    if (mode == 4) {
        n = rnd.next(150, 200);
        m = rnd.next(150, 200);
    }

    vector<int> shirts;
    vector<int> collars;

    if (mode == 0) {
        for (int i = 0; i < n; ++i) shirts.push_back(rnd.next(1, 1000));
        for (int i = 0; i < m; ++i) collars.push_back(rnd.next(1, 1000));
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) {
            shirts.push_back(rnd.next(1, 1000));
        }
        for (int i = 0; i < m; ++i) {
            collars.push_back(compatibleCollar(rnd.any(shirts)));
        }
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            int base = rnd.any(vector<int>{1, 2, 3, 4, 5, 999, 1000});
            shirts.push_back(base);
        }
        for (int i = 0; i < m; ++i) {
            collars.push_back(incompatibleCollar(rnd.any(shirts)));
        }
    } else if (mode == 3) {
        int groups = rnd.next(1, 5);
        vector<int> bases;
        for (int i = 0; i < groups; ++i) bases.push_back(rnd.next(1, 1000));

        for (int i = 0; i < n; ++i) shirts.push_back(rnd.any(bases));
        for (int i = 0; i < m; ++i) {
            int base = rnd.any(bases);
            collars.push_back(rnd.next(0, 1) ? compatibleCollar(base) : incompatibleCollar(base));
        }
    } else {
        for (int i = 0; i < n; ++i) shirts.push_back(rnd.next(1, 1000));
        for (int i = 0; i < m; ++i) {
            int shirt = rnd.any(shirts);
            collars.push_back(rnd.next(0, 2) == 0 ? incompatibleCollar(shirt) : compatibleCollar(shirt));
        }
    }

    shuffle(shirts.begin(), shirts.end());
    shuffle(collars.begin(), collars.end());

    println(n, m);
    for (int shirt : shirts) println(shirt);
    for (int collar : collars) println(collar);

    return 0;
}

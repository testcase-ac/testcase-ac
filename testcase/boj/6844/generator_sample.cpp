#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

const vector<int> FIXED_MOTELS = {
    0, 990, 1010, 1970, 2030, 2940, 3060,
    3930, 4060, 4970, 5030, 5990, 6010, 7000,
};

bool isAvailable(int m, const set<int>& used) {
    return 1 <= m && m <= 6999 && !used.count(m);
}

void addIfAvailable(vector<int>& added, set<int>& used, int m) {
    if (isAvailable(m, used)) {
        used.insert(m);
        added.push_back(m);
    }
}

void fillRandom(vector<int>& added, set<int>& used, int targetN) {
    while ((int)added.size() < targetN) {
        addIfAvailable(added, used, rnd.next(1, 6999));
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    set<int> used(FIXED_MOTELS.begin(), FIXED_MOTELS.end());
    vector<int> added;

    int mode = rnd.next(0, 5);
    int A = 1;
    int B = 7000;

    if (mode == 0) {
        A = rnd.next(1, 1100);
        B = rnd.next(A, min(1300, A + rnd.next(0, 300)));
    } else if (mode == 1) {
        A = rnd.next(900, 1030);
        B = rnd.next(A, 1100);
        int targetN = rnd.next(0, 6);
        fillRandom(added, used, targetN);
    } else if (mode == 2) {
        A = rnd.next(1, 80);
        B = rnd.next(A, 160);
        int start = rnd.next(1, 6800);
        int step = rnd.next(A, B);
        int targetN = rnd.next(8, 20);
        for (int i = 0; (int)added.size() < targetN && i < 35; ++i) {
            addIfAvailable(added, used, start + i * step);
        }
        fillRandom(added, used, targetN);
    } else if (mode == 3) {
        A = rnd.next(1, 500);
        B = rnd.next(6500, 7000);
        int targetN = rnd.next(10, 20);
        for (int m : {1, 2, 3, 6997, 6998, 6999}) {
            addIfAvailable(added, used, m);
        }
        fillRandom(added, used, targetN);
    } else if (mode == 4) {
        A = rnd.next(300, 1300);
        B = rnd.next(A, min(2500, A + rnd.next(0, 900)));
        int targetN = rnd.next(12, 20);
        for (int base : FIXED_MOTELS) {
            addIfAvailable(added, used, base - rnd.next(1, 40));
            if ((int)added.size() >= targetN) break;
            addIfAvailable(added, used, base + rnd.next(1, 40));
            if ((int)added.size() >= targetN) break;
        }
        fillRandom(added, used, targetN);
    } else {
        A = rnd.next(1, 7000);
        B = rnd.next(A, 7000);
        int targetN = rnd.next(0, 20);
        fillRandom(added, used, targetN);
    }

    shuffle(added.begin(), added.end());

    println(A);
    println(B);
    println((int)added.size());
    for (int m : added) {
        println(m);
    }

    return 0;
}

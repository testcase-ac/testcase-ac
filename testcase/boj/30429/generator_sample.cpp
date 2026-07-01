#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 1;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 6);
    } else {
        n = rnd.next(3, 14);
    }

    vector<int> alien(n + 1);
    int pattern = rnd.next(0, 3);
    for (int i = 1; i <= n; ++i) {
        if (pattern == 0) {
            alien[i] = 0;
        } else if (pattern == 1) {
            alien[i] = i % 2;
        } else if (pattern == 2) {
            alien[i] = (i == 1 ? 0 : 1);
        } else {
            alien[i] = rnd.next(0, 1);
        }
    }
    alien[rnd.next(1, n)] = 0;

    vector<int> target(n + 1);
    if (mode == 0) {
        target[1] = 1;
    } else if (mode == 1) {
        for (int i = 1; i <= n; ++i) {
            target[i] = i;
        }
    } else if (mode == 2) {
        for (int i = 1; i <= n; ++i) {
            target[i] = (i == n ? n : i + 1);
        }
    } else if (mode == 3) {
        for (int i = 1; i <= n; ++i) {
            target[i] = (i == n ? 1 : i + 1);
        }
    } else if (mode == 4) {
        int center = rnd.next(1, n);
        for (int i = 1; i <= n; ++i) {
            target[i] = center;
        }
    } else {
        for (int i = 1; i <= n; ++i) {
            target[i] = rnd.next(1, n);
        }
    }

    if (rnd.next(0, 3) == 0) {
        vector<int> perm(n + 1);
        for (int i = 1; i <= n; ++i) {
            perm[i] = i;
        }
        shuffle(perm.begin() + 1, perm.end());

        vector<int> remappedAlien(n + 1);
        vector<int> remappedTarget(n + 1);
        for (int oldId = 1; oldId <= n; ++oldId) {
            remappedAlien[perm[oldId]] = alien[oldId];
        }
        for (int oldId = 1; oldId <= n; ++oldId) {
            remappedTarget[perm[oldId]] = perm[target[oldId]];
        }
        alien = remappedAlien;
        target = remappedTarget;
    }

    println(n);
    for (int i = 1; i <= n; ++i) {
        println(target[i], alien[i] ^ alien[target[i]]);
    }

    return 0;
}

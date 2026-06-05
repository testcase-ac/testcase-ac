#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = rnd.next(2, 8);
    } else if (mode <= 3) {
        n = rnd.next(3, 35);
    } else {
        n = rnd.next(20, 80);
    }

    int z = rnd.next(2, n);
    vector<int> candidates;
    for (int field = 2; field <= n; ++field) {
        if (field != z) candidates.push_back(field);
    }

    set<int> obstacleSet;
    if (mode == 0) {
        // Leave the board open.
    } else if (mode == 1) {
        int m = rnd.next(0, min<int>(3, candidates.size()));
        shuffle(candidates.begin(), candidates.end());
        for (int i = 0; i < m; ++i) obstacleSet.insert(candidates[i]);
    } else if (mode == 2) {
        int m = rnd.next(max<int>(0, (int)candidates.size() / 2), (int)candidates.size());
        shuffle(candidates.begin(), candidates.end());
        for (int i = 0; i < m; ++i) obstacleSet.insert(candidates[i]);
    } else {
        int jumps = rnd.next(1, max(1, n - 1));
        int pos = 1;
        for (int step = 0; step < n; ++step) {
            pos += jumps;
            while (pos > n) pos -= n;
            if (pos == z) break;
            if (pos != 1 && rnd.next(0, 99) < 75) obstacleSet.insert(pos);
        }

        int extra = rnd.next(0, min<int>(8, candidates.size()));
        shuffle(candidates.begin(), candidates.end());
        for (int i = 0; i < extra; ++i) obstacleSet.insert(candidates[i]);
    }

    vector<int> obstacles(obstacleSet.begin(), obstacleSet.end());
    shuffle(obstacles.begin(), obstacles.end());

    println(n, z, (int)obstacles.size());
    println(obstacles);

    return 0;
}

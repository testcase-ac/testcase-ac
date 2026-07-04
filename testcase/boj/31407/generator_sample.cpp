#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int l;
    int n;

    if (mode == 0) {
        l = rnd.next(1, 8);
        n = rnd.next(1, l);
    } else if (mode == 1) {
        l = rnd.next(1, 12);
        n = l;
    } else if (mode == 2) {
        l = rnd.next(40, 100);
        n = rnd.next(1, min(70, l));
    } else if (mode == 3) {
        l = rnd.next(8, 30);
        n = rnd.next(max(1, l / 2), l);
    } else if (mode == 4) {
        l = rnd.next(2, 100);
        n = rnd.next(1, min(10, l));
    } else {
        l = rnd.next(70, 100);
        n = rnd.next(50, 70);
    }

    vector<int> positions(l);
    for (int i = 0; i < l; ++i) {
        positions[i] = i;
    }

    if (mode == 3) {
        int window = rnd.next(n, min(l, n + 8));
        int start = rnd.next(0, l - window);
        positions.clear();
        for (int p = start; p < start + window; ++p) {
            positions.push_back(p);
        }
    }

    shuffle(positions.begin(), positions.end());
    positions.resize(n);

    if (mode == 4) {
        sort(positions.begin(), positions.end());
    } else if (rnd.next(0, 1) == 0) {
        sort(positions.begin(), positions.end());
    }

    vector<string> dirs;
    dirs.reserve(n);
    for (int i = 0; i < n; ++i) {
        if (mode == 0) {
            dirs.push_back(rnd.next(0, 1) == 0 ? "L" : "R");
        } else if (mode == 1 || mode == 3) {
            dirs.push_back(i % 2 == 0 ? "L" : "R");
        } else if (mode == 4) {
            dirs.push_back(rnd.next(0, 9) == 0 ? "R" : "L");
        } else if (mode == 5) {
            dirs.push_back(rnd.next(0, 9) == 0 ? "L" : "R");
        } else {
            dirs.push_back(rnd.next(0, 1) == 0 ? "L" : "R");
        }
    }

    if (rnd.next(0, 1) == 0) {
        vector<int> order(n);
        for (int i = 0; i < n; ++i) {
            order[i] = i;
        }
        shuffle(order.begin(), order.end());

        vector<int> shuffledPositions;
        vector<string> shuffledDirs;
        shuffledPositions.reserve(n);
        shuffledDirs.reserve(n);
        for (int idx : order) {
            shuffledPositions.push_back(positions[idx]);
            shuffledDirs.push_back(dirs[idx]);
        }
        positions = shuffledPositions;
        dirs = shuffledDirs;
    }

    println(n, l);
    for (int i = 0; i < n; ++i) {
        println(positions[i], dirs[i]);
    }

    return 0;
}

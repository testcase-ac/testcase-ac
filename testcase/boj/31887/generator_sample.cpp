#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

void addIfValid(set<int>& positions, int n, int x) {
    if (1 <= x && x <= 2 * n - 1 && x != n) {
        positions.insert(x);
    }
}

int randomPosition(int n) {
    int x = rnd.next(1, 2 * n - 2);
    if (x >= n) {
        ++x;
    }
    return x;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 5) {
        n = rnd.next(100000, 1000000);
    } else if (mode == 0) {
        n = rnd.next(2, 5);
    } else {
        n = rnd.next(6, 40);
    }

    set<int> positions;

    if (mode == 0) {
        int limit = 2 * n - 1;
        for (int x = 1; x <= limit; ++x) {
            addIfValid(positions, n, x);
        }
    } else if (mode == 1) {
        addIfValid(positions, n, 1);
        addIfValid(positions, n, 2 * n - 1);
        addIfValid(positions, n, n - 1);
        addIfValid(positions, n, n + 1);
    } else if (mode == 2) {
        int radius = rnd.next(1, min(n - 1, 8));
        for (int d = 1; d <= radius; ++d) {
            addIfValid(positions, n, n - d);
            addIfValid(positions, n, n + d);
        }
    } else if (mode == 3) {
        int pairs = rnd.next(1, min(n - 1, 12));
        for (int i = 0; i < pairs; ++i) {
            int left = rnd.next(1, n - 1);
            addIfValid(positions, n, left);
            addIfValid(positions, n, left + n);
        }
    } else if (mode == 4) {
        int blockLen = rnd.next(1, min(n - 1, 10));
        int leftStart = rnd.next(1, n - blockLen);
        int rightStart = rnd.next(n + 1, 2 * n - blockLen);
        for (int i = 0; i < blockLen; ++i) {
            addIfValid(positions, n, leftStart + i);
            addIfValid(positions, n, rightStart + i);
        }
    } else {
        addIfValid(positions, n, 1);
        addIfValid(positions, n, n - 1);
        addIfValid(positions, n, n + 1);
        addIfValid(positions, n, 2 * n - 1);
        int extra = rnd.next(0, 8);
        while ((int)positions.size() < 4 + extra) {
            addIfValid(positions, n, randomPosition(n));
        }
    }

    int target = rnd.next(1, min(2 * n - 2, max(1, (int)positions.size() + 8)));
    while ((int)positions.size() < target) {
        addIfValid(positions, n, randomPosition(n));
    }

    vector<int> answer(positions.begin(), positions.end());
    shuffle(answer.begin(), answer.end());

    println(n, (int)answer.size());
    println(answer);

    return 0;
}

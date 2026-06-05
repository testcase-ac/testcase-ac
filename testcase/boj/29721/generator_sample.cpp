#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    vector<pair<int, int>> pieces;
    set<pair<int, int>> used;

    auto addPiece = [&](int x, int y) {
        if (1 <= x && x <= n && 1 <= y && y <= n && used.insert({x, y}).second) {
            pieces.push_back({x, y});
        }
    };

    auto addRandomPiece = [&]() {
        for (int tries = 0; tries < 200; ++tries) {
            int x = rnd.next(1, n);
            int y = rnd.next(1, n);
            if (used.insert({x, y}).second) {
                pieces.push_back({x, y});
                return;
            }
        }
        for (int x = 1; x <= n; ++x) {
            for (int y = 1; y <= n; ++y) {
                if (used.insert({x, y}).second) {
                    pieces.push_back({x, y});
                    return;
                }
            }
        }
    };

    if (mode == 0) {
        n = rnd.next(1, 4);
        int target = rnd.next(1, min(n * n, 12));
        while ((int)pieces.size() < target) addRandomPiece();
    } else if (mode == 1) {
        n = rnd.next(3, 9);
        int target = rnd.next(1, min(n * n, 30));
        int startX = rnd.next(1, min(n, 3));
        int startY = rnd.next(1, min(n, 3));
        for (int x = startX; x <= n && (int)pieces.size() < target; x += 2) {
            for (int y = startY; y <= n && (int)pieces.size() < target; y += 2) {
                addPiece(x, y);
            }
        }
        while ((int)pieces.size() < target) addRandomPiece();
    } else if (mode == 2) {
        n = rnd.next(5, 20);
        int target = rnd.next(4, min(n * n, 45));
        for (int x = 1; x <= n && (int)pieces.size() < target; ++x) {
            addPiece(x, 1);
            addPiece(x, n);
        }
        for (int y = 2; y < n && (int)pieces.size() < target; ++y) {
            addPiece(1, y);
            addPiece(n, y);
        }
        while ((int)pieces.size() < target) addRandomPiece();
    } else if (mode == 3) {
        n = rnd.next(4, 18);
        int blockSize = rnd.next(2, min(n, 6));
        int baseX = rnd.next(1, n - blockSize + 1);
        int baseY = rnd.next(1, n - blockSize + 1);
        for (int x = baseX; x < baseX + blockSize; ++x) {
            for (int y = baseY; y < baseY + blockSize; ++y) {
                if (rnd.next(0, 1)) addPiece(x, y);
            }
        }
        if (pieces.empty()) addPiece(baseX, baseY);
        int extras = rnd.next(0, 12);
        while (extras-- > 0) addRandomPiece();
    } else if (mode == 4) {
        n = rnd.next(50, 100000);
        int target = rnd.next(1, 35);
        vector<pair<int, int>> anchors = {
            {1, 1}, {1, n}, {n, 1}, {n, n}, {1, rnd.next(1, n)}, {n, rnd.next(1, n)},
            {rnd.next(1, n), 1}, {rnd.next(1, n), n}
        };
        shuffle(anchors.begin(), anchors.end());
        for (auto [x, y] : anchors) addPiece(x, y);
        while ((int)pieces.size() < target) addRandomPiece();
    } else {
        n = rnd.next(6, 100);
        int target = rnd.next(8, min(n * n, 80));
        int centerX = rnd.next(3, n - 2);
        int centerY = rnd.next(3, n - 2);
        addPiece(centerX, centerY);
        addPiece(centerX - 2, centerY);
        addPiece(centerX + 2, centerY);
        addPiece(centerX, centerY - 2);
        addPiece(centerX, centerY + 2);
        while ((int)pieces.size() < target) addRandomPiece();
    }

    shuffle(pieces.begin(), pieces.end());

    println(n, (int)pieces.size());
    for (auto [x, y] : pieces) {
        println(x, y);
    }

    return 0;
}

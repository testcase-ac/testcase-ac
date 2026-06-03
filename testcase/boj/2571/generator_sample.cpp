#include "testlib.h"
#include <utility>
#include <vector>
using namespace std;

int clampCoord(int v) {
    if (v < 1) return 1;
    if (v > 90) return 90;
    return v;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    vector<pair<int, int>> papers;

    if (mode == 0) {
        n = rnd.next(1, 8);
        int baseX = rnd.next(1, 90);
        int baseY = rnd.next(1, 90);
        for (int i = 0; i < n; ++i) {
            int x = clampCoord(baseX + rnd.next(-6, 6));
            int y = clampCoord(baseY + rnd.next(-6, 6));
            papers.push_back({x, y});
        }
    } else if (mode == 1) {
        n = rnd.next(6, 18);
        int y = rnd.next(1, 90);
        int start = rnd.next(1, 20);
        int step = rnd.next(1, 8);
        for (int i = 0; i < n; ++i) {
            int x = clampCoord(start + i * step + rnd.next(-2, 2));
            papers.push_back({x, clampCoord(y + rnd.next(-3, 3))});
        }
    } else if (mode == 2) {
        n = rnd.next(6, 20);
        int x = rnd.next(1, 90);
        int start = rnd.next(1, 20);
        int step = rnd.next(1, 8);
        for (int i = 0; i < n; ++i) {
            int y = clampCoord(start + i * step + rnd.next(-2, 2));
            papers.push_back({clampCoord(x + rnd.next(-3, 3)), y});
        }
    } else if (mode == 3) {
        n = rnd.next(8, 28);
        int startX = rnd.next(1, 35);
        int startY = rnd.next(1, 35);
        int step = rnd.next(2, 6);
        for (int i = 0; i < n; ++i) {
            int x = clampCoord(startX + i * step + rnd.next(-2, 2));
            int y = clampCoord(startY + i * step + rnd.next(-2, 2));
            papers.push_back({x, y});
        }
    } else if (mode == 4) {
        n = rnd.next(12, 36);
        vector<pair<int, int>> anchors = {{1, 1}, {1, 81}, {81, 1}, {81, 81}, {40, 40}};
        for (int i = 0; i < n; ++i) {
            auto anchor = rnd.any(anchors);
            int x = clampCoord(anchor.first + rnd.next(-8, 8));
            int y = clampCoord(anchor.second + rnd.next(-8, 8));
            papers.push_back({x, y});
        }
    } else {
        n = rnd.next(20, 100);
        int loX = rnd.next(1, 70);
        int loY = rnd.next(1, 70);
        int hiX = rnd.next(loX, 90);
        int hiY = rnd.next(loY, 90);
        for (int i = 0; i < n; ++i) {
            papers.push_back({rnd.next(loX, hiX), rnd.next(loY, hiY)});
        }
    }

    shuffle(papers.begin(), papers.end());

    println(n);
    for (auto paper : papers) {
        println(paper.first, paper.second);
    }

    return 0;
}

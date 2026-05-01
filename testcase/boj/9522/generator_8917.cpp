#include "testlib.h"
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<int,int>> pts;

    int scenario = rnd.next(0, 7);

    if (scenario == 0) {
        // Single point
        int x = rnd.next(1, 20);
        int y = rnd.next(1, 20);
        pts.push_back({x, y});
    } else if (scenario == 1) {
        // Short diagonal chain
        int k = rnd.next(2, 6);
        int x0 = rnd.next(1, 20);
        int y0 = rnd.next(1, 20);
        for (int i = 0; i < k; i++) {
            pts.push_back({x0 + i, y0 + i});
        }
    } else if (scenario == 2) {
        // Vertical star: one x, many distinct y
        int k = rnd.next(2, 8);
        int x = rnd.next(1, 30);
        int baseY = rnd.next(1, 30);
        for (int i = 0; i < k; i++) {
            pts.push_back({x, baseY + i});
        }
    } else if (scenario == 3) {
        // Horizontal star: one y, many distinct x
        int k = rnd.next(2, 8);
        int y = rnd.next(1, 30);
        int baseX = rnd.next(1, 30);
        for (int i = 0; i < k; i++) {
            pts.push_back({baseX + i, y});
        }
    } else if (scenario == 4) {
        // Path-like structure in bipartite graph (ladder path)
        int t = rnd.next(2, 6); // number of Y vertices; X = t + 1
        int baseX = rnd.next(1, 30);
        int baseY = rnd.next(1, 30);

        // Y vertices: baseY .. baseY + t - 1
        // X vertices: baseX .. baseX + t
        for (int i = 0; i < t; i++) {
            int xi1 = baseX + i;
            int xi2 = baseX + i + 1;
            int yi  = baseY + i;
            pts.push_back({xi1, yi});
            pts.push_back({xi2, yi});
        }
    } else if (scenario == 5) {
        // Two disconnected components:
        // Component 1: vertical star
        int k1 = rnd.next(2, 5);
        int x1 = 1;
        int baseY1 = 1;
        for (int i = 0; i < k1; i++) {
            pts.push_back({x1, baseY1 + i});
        }

        // Component 2: 2x2 grid, separated in coordinates
        int xA = 50, xB = 51;
        int yA = 50, yB = 51;
        pts.push_back({xA, yA});
        pts.push_back({xA, yB});
        pts.push_back({xB, yA});
        pts.push_back({xB, yB});
    } else if (scenario == 6) {
        // Random small bipartite graph with moderate density
        int Xc = rnd.next(1, 5);
        int Yc = rnd.next(1, 5);
        int pChoice = rnd.next(0, 2);
        double p = (pChoice == 0 ? 0.35 : (pChoice == 1 ? 0.6 : 0.85));

        int baseX = rnd.next(1, 20);
        int baseY = rnd.next(1, 20);

        for (int i = 0; i < Xc; i++) {
            for (int j = 0; j < Yc; j++) {
                if (rnd.next() < p) {
                    pts.push_back({baseX + i, baseY + j});
                }
            }
        }
        // Ensure at least one point
        if (pts.empty()) {
            int xi = rnd.next(0, Xc - 1);
            int yi = rnd.next(0, Yc - 1);
            pts.push_back({baseX + xi, baseY + yi});
        }
    } else if (scenario == 7) {
        // Dense small grid (potential for many even cycles)
        int Xc = rnd.next(3, 5);
        int Yc = rnd.next(3, 5);
        int baseX = rnd.next(1, 20);
        int baseY = rnd.next(1, 20);
        for (int i = 0; i < Xc; i++) {
            for (int j = 0; j < Yc; j++) {
                pts.push_back({baseX + i, baseY + j});
            }
        }
    }

    // Deduplicate points just in case (validator forbids duplicates)
    sort(pts.begin(), pts.end());
    pts.erase(unique(pts.begin(), pts.end()), pts.end());

    // Safety: ensure non-empty (should always be, but be robust)
    if (pts.empty()) {
        pts.push_back({1, 1});
    }

    // Optional shuffle of points for variety
    if (rnd.next(0, 1) == 1) {
        shuffle(pts.begin(), pts.end());
    }

    // Global random shift to spread coordinates within [1, 500]
    int maxX = 0, maxY = 0;
    for (auto &p : pts) {
        if (p.first > maxX) maxX = p.first;
        if (p.second > maxY) maxY = p.second;
    }
    int shiftX = rnd.next(0, 500 - maxX);
    int shiftY = rnd.next(0, 500 - maxY);
    for (auto &p : pts) {
        p.first += shiftX;
        p.second += shiftY;
    }

    int N = (int)pts.size();
    println(N);
    for (auto &p : pts) {
        println(p.first, p.second);
    }

    return 0;
}

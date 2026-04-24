#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose small number of stars
    int N = rnd.next(2, 10);

    // Hyper-parameter: choose a distribution mode
    // 0 = uniform random, 1 = all colinear, 2 = two clusters
    int mode = rnd.next(0, 2);

    set<pair<int,int>> used;
    vector<pair<int,int>> pts;
    pts.reserve(N);

    if (mode == 0) {
        // Uniform random points in [-100,100]^2
        while ((int)pts.size() < N) {
            int x = rnd.next(-100, 100);
            int y = rnd.next(-100, 100);
            if (used.insert({x,y}).second) {
                pts.emplace_back(x,y);
            }
        }
    } else if (mode == 1) {
        // Colinear points: choose a base point and direction
        int x0 = rnd.next(-50, 50);
        int y0 = rnd.next(-50, 50);
        // direction vector (dx,dy) non-zero
        int dx, dy;
        do {
            dx = rnd.next(-5, 5);
            dy = rnd.next(-5, 5);
        } while (dx == 0 && dy == 0);
        while ((int)pts.size() < N) {
            int t = rnd.next(-50, 50);
            int x = x0 + dx * t;
            int y = y0 + dy * t;
            if (used.insert({x,y}).second) {
                pts.emplace_back(x,y);
            }
        }
    } else {
        // Two clusters
        // pick two centers
        int cx1 = rnd.next(-50, 50), cy1 = rnd.next(-50, 50);
        int cx2 = rnd.next(-50, 50), cy2 = rnd.next(-50, 50);
        while (cx1 == cx2 && cy1 == cy2) {
            cx2 = rnd.next(-50, 50);
            cy2 = rnd.next(-50, 50);
        }
        while ((int)pts.size() < N) {
            // assign to cluster 1 or 2
            bool c1 = rnd.next(0,1) == 0;
            int cx = c1 ? cx1 : cx2;
            int cy = c1 ? cy1 : cy2;
            // small offset around center
            int dx = rnd.next(-10, 10);
            int dy = rnd.next(-10, 10);
            int x = cx + dx;
            int y = cy + dy;
            if (used.insert({x,y}).second) {
                pts.emplace_back(x,y);
            }
        }
    }

    // Shuffle the points to randomize order
    shuffle(pts.begin(), pts.end());

    // Output
    println(N);
    for (auto &p : pts) {
        println(p.first, p.second);
    }
    return 0;
}

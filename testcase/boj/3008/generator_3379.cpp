#include "testlib.h"
#include <vector>
#include <set>
#include <cmath>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of points
    int N = rnd.next(3, 10);
    vector<pair<long long, long long>> pts;
    int pattern = rnd.next(0, 2);
    if (pattern == 0) {
        // Uniform random points in [-10,10]×[-10,10]
        set<pair<int,int>> used;
        while ((int)pts.size() < N) {
            int x = rnd.next(-10, 10);
            int y = rnd.next(-10, 10);
            if (used.insert({x, y}).second) {
                pts.emplace_back(x, y);
            }
        }
    } else if (pattern == 1) {
        // Grid pattern
        int d = rnd.next(1, 3);
        int g = (int)ceil(sqrt(N));
        int startx = rnd.next(-10, 0);
        int starty = rnd.next(-10, 0);
        for (int i = 0; i < g && (int)pts.size() < N; i++) {
            for (int j = 0; j < g && (int)pts.size() < N; j++) {
                long long x = startx + i * d;
                long long y = starty + j * d;
                pts.emplace_back(x, y);
            }
        }
    } else {
        // L-shape: some on a horizontal line, some on a vertical line
        int n1 = rnd.next(1, N - 1);
        int y0 = rnd.next(-10, 10);
        int x0 = rnd.next(-10, 10);
        set<pair<int,int>> used;
        // Horizontal line y=y0
        while ((int)pts.size() < n1) {
            int x = rnd.next(-10, 10);
            if (used.insert({x, y0}).second) {
                pts.emplace_back(x, y0);
            }
        }
        // Vertical line x=x0
        while ((int)pts.size() < N) {
            int y = rnd.next(-10, 10);
            if (used.insert({x0, y}).second) {
                pts.emplace_back(x0, y);
            }
        }
    }
    // Shuffle for randomness
    shuffle(pts.begin(), pts.end());
    // Output
    println(N);
    for (auto &p : pts) {
        println(p.first, p.second);
    }
    return 0;
}

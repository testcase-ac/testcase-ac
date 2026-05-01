#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
#include <cmath>
#include <climits>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of fields
    int N = rnd.next(2, 10);
    vector<pair<int,int>> pts;
    pts.reserve(N);
    set<pair<int,int>> used;

    // Choose distribution type: 0=uniform, 1=clusters, 2=line with noise
    int distType = rnd.next(0, 2);
    if (distType == 0) {
        // Uniform random distinct points
        while ((int)pts.size() < N) {
            int x = rnd.next(0, 1000);
            int y = rnd.next(0, 1000);
            if (used.insert({x, y}).second) {
                pts.emplace_back(x, y);
            }
        }
    } else if (distType == 1) {
        // Clusters
        int k = rnd.next(1, min(4, N));
        vector<pair<int,int>> centers;
        for (int i = 0; i < k; i++) {
            centers.emplace_back(rnd.next(0, 1000), rnd.next(0, 1000));
        }
        while ((int)pts.size() < N) {
            auto c = centers[rnd.next(0, k-1)];
            int x = c.first + rnd.next(-50, 50);
            int y = c.second + rnd.next(-50, 50);
            x = max(0, min(1000, x));
            y = max(0, min(1000, y));
            if (used.insert({x, y}).second) {
                pts.emplace_back(x, y);
            }
        }
    } else {
        // Line with noise
        int x1 = rnd.next(0, 1000), y1 = rnd.next(0, 1000);
        int x2 = rnd.next(0, 1000), y2 = rnd.next(0, 1000);
        while (x1 == x2 && y1 == y2) {
            x2 = rnd.next(0, 1000);
            y2 = rnd.next(0, 1000);
        }
        for (int i = 0; i < N; i++) {
            double t = (N == 1 ? 0.0 : double(i) / (N - 1));
            double xf = x1 + (x2 - x1) * t + rnd.next(-20, 20);
            double yf = y1 + (y2 - y1) * t + rnd.next(-20, 20);
            int x = max(0, min(1000, int(round(xf))));
            int y = max(0, min(1000, int(round(yf))));
            if (!used.count({x, y})) {
                used.insert({x, y});
                pts.emplace_back(x, y);
            } else {
                // jitter until unique
                int tries = 0;
                while (tries < 10) {
                    x = rnd.next(0, 1000);
                    y = rnd.next(0, 1000);
                    if (used.insert({x, y}).second) {
                        pts.emplace_back(x, y);
                        break;
                    }
                    tries++;
                }
                if ((int)pts.size() < i+1) {
                    // fallback uniform
                    do {
                        x = rnd.next(0, 1000);
                        y = rnd.next(0, 1000);
                    } while (!used.insert({x, y}).second);
                    pts.emplace_back(x, y);
                }
            }
        }
    }

    // Compute minimum squared distance between any two points
    long long dmin = LLONG_MAX;
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            long long dx = pts[i].first - pts[j].first;
            long long dy = pts[i].second - pts[j].second;
            long long d = dx*dx + dy*dy;
            if (d > 0 && d < dmin) dmin = d;
        }
    }
    if (dmin == LLONG_MAX) dmin = 1;
    // Choose C so that all edges are allowed (connectivity guaranteed)
    int C = rnd.next(1, (int)min(dmin, 1000000LL));

    // Output
    println(N, C);
    for (auto &p : pts) {
        println(p.first, p.second);
    }

    return 0;
}

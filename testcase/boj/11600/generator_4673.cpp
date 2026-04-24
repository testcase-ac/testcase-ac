#include "testlib.h"
#include <vector>
#include <set>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of points
    int n = rnd.next(1, 10);
    // Choose odd S in a small range
    int k = rnd.next(3, 25);
    int S = 2 * k + 1;

    // Hyper-parameters
    double uniformP = rnd.next();  // probability of uniform distribution
    int c = rnd.next(1, min(n, 3)); // number of clusters

    // Build cluster centers and radii
    vector<pair<int,int>> centers;
    vector<int> radii;
    for (int i = 0; i < c; i++) {
        int cx = rnd.next(0, S);
        int cy = rnd.next(0, S);
        // biased radius for diversity
        int r = rnd.wnext(S/4 + 1, rnd.next(-3, 3));
        centers.emplace_back(cx, cy);
        radii.push_back(r);
    }

    // Generate unique points and identifiers
    set<pair<int,int>> usedPos;
    set<string> usedId;
    struct P { int x, y; string id; };
    vector<P> pts;

    const string alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                         "abcdefghijklmnopqrstuvwxyz"
                         "0123456789";

    while ((int)pts.size() < n) {
        int x, y;
        if (rnd.next() < uniformP) {
            // Uniform point
            x = rnd.next(0, S);
            y = rnd.next(0, S);
        } else {
            // Clustered point
            int idx = rnd.next(0, c - 1);
            int cx = centers[idx].first;
            int cy = centers[idx].second;
            int r = radii[idx];
            int dx = rnd.next(-r, r);
            int dy = rnd.next(-r, r);
            x = cx + dx;
            y = cy + dy;
            // clamp
            if (x < 0) x = 0;
            if (x > S) x = S;
            if (y < 0) y = 0;
            if (y > S) y = S;
        }
        if (!usedPos.insert({x,y}).second) continue;

        // Generate unique identifier
        string id;
        do {
            id.clear();
            int len = rnd.next(1, 10);
            for (int j = 0; j < len; j++)
                id.push_back(rnd.any(alpha));
        } while (!usedId.insert(id).second);

        pts.push_back({x, y, id});
    }

    // Shuffle output order
    shuffle(pts.begin(), pts.end());

    // Output
    println(n, S);
    for (auto &p : pts) {
        println(p.x, p.y, p.id);
    }

    return 0;
}

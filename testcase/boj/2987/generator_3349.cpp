#include "testlib.h"
#include <bits/stdc++.h>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Generate a non-degenerate triangle with integer vertices in [1,20]
    int xA, yA, xB, yB, xC, yC;
    auto area2 = [&](int x1, int y1, int x2, int y2, int x3, int y3) {
        return abs(x1*(y2 - y3) + x2*(y3 - y1) + x3*(y1 - y2));
    };
    do {
        xA = rnd.next(1,20);
        yA = rnd.next(1,20);
        xB = rnd.next(1,20);
        yB = rnd.next(1,20);
        xC = rnd.next(1,20);
        yC = rnd.next(1,20);
    } while (area2(xA,yA,xB,yB,xC,yC) == 0);

    // Collect boundary lattice points
    vector<pair<int,int>> border;
    auto collect_edge = [&](int x1,int y1,int x2,int y2) {
        int dx = x2 - x1, dy = y2 - y1;
        int g = gcd(abs(dx), abs(dy));
        for (int k = 0; k <= g; k++) {
            int xi = x1 + k * dx / g;
            int yi = y1 + k * dy / g;
            border.emplace_back(xi, yi);
        }
    };
    collect_edge(xA,yA,xB,yB);
    collect_edge(xB,yB,xC,yC);
    collect_edge(xC,yC,xA,yA);
    sort(border.begin(), border.end());
    border.erase(unique(border.begin(), border.end()), border.end());

    // Collect interior lattice points within bounding box
    int xmin = min({xA,xB,xC});
    int xmax = max({xA,xB,xC});
    int ymin = min({yA,yB,yC});
    int ymax = max({yA,yB,yC});
    vector<pair<int,int>> interior;
    for (int x = xmin; x <= xmax; x++) {
        for (int y = ymin; y <= ymax; y++) {
            // skip boundary
            if (binary_search(border.begin(), border.end(), make_pair(x,y)))
                continue;
            // check inside by area sum
            int a1 = area2(x,y, xA,yA, xB,yB);
            int a2 = area2(x,y, xB,yB, xC,yC);
            int a3 = area2(x,y, xC,yC, xA,yA);
            if (a1 + a2 + a3 == area2(xA,yA,xB,yB,xC,yC))
                interior.emplace_back(x,y);
        }
    }

    // Collect outside lattice points in [1,20]x[1,20]
    vector<pair<int,int>> outside;
    for (int x = 1; x <= 20; x++) {
        for (int y = 1; y <= 20; y++) {
            pair<int,int> p = {x,y};
            if (binary_search(border.begin(), border.end(), p)) continue;
            if (binary_search(interior.begin(), interior.end(), p)) continue;
            outside.push_back(p);
        }
    }

    // Number of trees
    int N = rnd.next(1, 10);
    // Decide how many inside, on-border, outside
    int max_in = min<int>(N, interior.size());
    int p_in = rnd.next(0, max_in);
    int max_on = min<int>(N - p_in, border.size());
    int p_on = rnd.next(0, max_on);
    int p_out = N - p_in - p_on;

    // Sample distinct points
    vector<pair<int,int>> trees;
    if (p_in > 0) {
        shuffle(interior.begin(), interior.end());
        for (int i = 0; i < p_in; i++)
            trees.push_back(interior[i]);
    }
    if (p_on > 0) {
        shuffle(border.begin(), border.end());
        for (int i = 0; i < p_on; i++)
            trees.push_back(border[i]);
    }
    if (p_out > 0) {
        shuffle(outside.begin(), outside.end());
        for (int i = 0; i < p_out; i++)
            trees.push_back(outside[i]);
    }
    // Shuffle the final list
    shuffle(trees.begin(), trees.end());

    // Output
    println(xA, yA);
    println(xB, yB);
    println(xC, yC);
    println(N);
    for (auto &p : trees)
        println(p.first, p.second);

    return 0;
}

#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll cross(const pair<int,int>& a, const pair<int,int>& b, const pair<int,int>& c) {
    // cross of (b-a) x (c-a)
    ll x1 = b.first - a.first;
    ll y1 = b.second - a.second;
    ll x2 = c.first - a.first;
    ll y2 = c.second - a.second;
    return x1 * y2 - x2 * y1;
}

bool collinear(const pair<int,int>& a,
               const pair<int,int>& b,
               const pair<int,int>& c) {
    return cross(a,b,c) == 0;
}

// check strictly inside convex polygon hull (CCW)
bool strictlyInsideConvex(const vector<pair<int,int>>& hull, const pair<int,int>& p) {
    int h = hull.size();
    for (int i = 0; i < h; i++) {
        auto a = hull[i];
        auto b = hull[(i+1)%h];
        if (cross(a, b, p) <= 0) return false;
    }
    return true;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // hyperparameter: type of pointset
    int type = rnd.next(0, 2);
    int N = rnd.next(3, 10);
    const int MAXC = 1000;
    vector<pair<int,int>> S;

    if (type == 0) {
        // all points on convex hull: generate perturbed circle
        double R = rnd.next(100, 500);
        int n = N;
        vector<double> ang(n);
        for (int i = 0; i < n; i++) {
            double base = 2*M_PI*i/n;
            double delta = (rnd.next() - 0.5) * (M_PI/n);
            ang[i] = base + delta;
        }
        sort(ang.begin(), ang.end());
        set<pair<int,int>> seen;
        for (int i = 0; i < n; i++) {
            int xi = int(round(R * cos(ang[i])));
            int yi = int(round(R * sin(ang[i])));
            // ensure unique
            if (seen.insert({xi, yi}).second) {
                S.emplace_back(xi, yi);
            } else {
                // perturb a bit if duplicate
                xi += i+1; yi -= i+2;
                S.emplace_back(xi, yi);
                seen.insert({xi, yi});
            }
        }
    }
    else if (type == 1) {
        // uniform random general position by rejection
        while ((int)S.size() < N) {
            int x = rnd.next(-MAXC, MAXC);
            int y = rnd.next(-MAXC, MAXC);
            pair<int,int> p = {x,y};
            bool ok = true;
            for (auto& q : S) if (q == p) { ok = false; break; }
            if (!ok) continue;
            // no collinear with any pair
            for (int i = 0; i < (int)S.size() && ok; i++) {
                for (int j = i+1; j < (int)S.size(); j++) {
                    if (collinear(S[i], S[j], p)) {
                        ok = false; break;
                    }
                }
            }
            if (ok) S.push_back(p);
        }
    }
    else {
        // cluster: some hull, some interior
        int h = rnd.next(3, N);
        // generate hull as type0
        double R = rnd.next(200, 500);
        vector<double> ang(h);
        for (int i = 0; i < h; i++) {
            double base = 2*M_PI*i/h;
            double delta = (rnd.next() - 0.5) * (M_PI/h);
            ang[i] = base + delta;
        }
        sort(ang.begin(), ang.end());
        vector<pair<int,int>> hull;
        set<pair<int,int>> seen;
        for (int i = 0; i < h; i++) {
            int xi = int(round(R * cos(ang[i])));
            int yi = int(round(R * sin(ang[i])));
            if (seen.insert({xi, yi}).second) {
                hull.emplace_back(xi, yi);
            } else {
                xi += i+3; yi -= i+4;
                hull.emplace_back(xi, yi);
                seen.insert({xi, yi});
            }
        }
        // add hull to S
        S = hull;
        // bounding box
        int minx = hull[0].first, maxx = hull[0].first;
        int miny = hull[0].second, maxy = hull[0].second;
        for (auto& p : hull) {
            minx = min(minx, p.first);
            maxx = max(maxx, p.first);
            miny = min(miny, p.second);
            maxy = max(maxy, p.second);
        }
        // generate interior points
        while ((int)S.size() < N) {
            int x = rnd.next(minx+1, maxx-1);
            int y = rnd.next(miny+1, maxy-1);
            auto p = make_pair(x,y);
            if (seen.count(p)) continue;
            if (!strictlyInsideConvex(hull, p)) continue;
            // no collinear with any existing two
            bool ok = true;
            for (int i = 0; i < (int)S.size() && ok; i++) {
                for (int j = i+1; j < (int)S.size(); j++) {
                    if (collinear(S[i], S[j], p)) {
                        ok = false; break;
                    }
                }
            }
            if (!ok) continue;
            seen.insert(p);
            S.push_back(p);
        }
    }

    // final shuffle
    shuffle(S.begin(), S.end());
    // output
    println(N);
    for (auto& p : S) println(p.first, p.second);
    return 0;
}

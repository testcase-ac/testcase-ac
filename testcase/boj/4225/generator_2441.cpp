/* generator code */
#include "testlib.h"
#include <vector>
#include <algorithm>
#include <set>
using namespace std;
struct Pt {
    int x, y;
};
long long cross(const Pt &O, const Pt &A, const Pt &B) {
    return (A.x - O.x) * (long long)(B.y - O.y) - (A.y - O.y) * (long long)(B.x - O.x);
}
vector<Pt> convexHull(vector<Pt> pts) {
    sort(pts.begin(), pts.end(), [](const Pt &a, const Pt &b) {
        if (a.x != b.x) return a.x < b.x;
        return a.y < b.y;
    });
    int n = pts.size(), k = 0;
    if (n <= 1) return pts;
    vector<Pt> H(2*n);
    // lower hull
    for (int i = 0; i < n; i++) {
        while (k >= 2 && cross(H[k-2], H[k-1], pts[i]) <= 0) k--;
        H[k++] = pts[i];
    }
    // upper hull
    for (int i = n-2, t = k+1; i >= 0; i--) {
        while (k >= t && cross(H[k-2], H[k-1], pts[i]) <= 0) k--;
        H[k++] = pts[i];
    }
    H.resize(k-1);
    return H;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int T = rnd.next(1, 3);
    for (int tc = 0; tc < T; tc++) {
        vector<Pt> pts;
        // generate random unique points until convex hull has >=3 pts
        while (true) {
            pts.clear();
            set<pair<int,int>> seen;
            int P = rnd.next(3, 10);
            while ((int)pts.size() < P) {
                int x = rnd.next(0, 100);
                int y = rnd.next(0, 100);
                if (seen.insert({x,y}).second) {
                    pts.push_back({x,y});
                }
            }
            vector<Pt> hull = convexHull(pts);
            if ((int)hull.size() >= 3) {
                // output this hull
                println((int)hull.size());
                for (auto &p : hull) {
                    println(p.x, p.y);
                }
                break;
            }
            // else retry
        }
    }
    println(0);
    return 0;
}

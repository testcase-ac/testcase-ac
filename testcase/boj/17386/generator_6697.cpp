#include "testlib.h"
#include <vector>
using namespace std;
using ll = long long;

ll orient(pair<ll,ll> a, pair<ll,ll> b, pair<ll,ll> c) {
    return (b.first - a.first) * (c.second - a.second)
         - (b.second - a.second) * (c.first - a.first);
}

bool properIntersect(pair<ll,ll> a, pair<ll,ll> b, pair<ll,ll> c, pair<ll,ll> d) {
    ll o1 = orient(a,b,c), o2 = orient(a,b,d);
    ll o3 = orient(c,d,a), o4 = orient(c,d,b);
    return (o1 > 0 && o2 < 0 || o1 < 0 && o2 > 0)
        && (o3 > 0 && o4 < 0 || o3 < 0 && o4 > 0);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyperparameters: bound sizes and axis-aligned chance
    vector<int> bounds = {10, 100, 1000, 1000000};
    int B = rnd.any(bounds);
    bool wantIntersect = rnd.next(0, 1) == 1;
    bool axis1 = rnd.next(0, 1) == 1;
    bool axis2 = rnd.next(0, 1) == 1;

    pair<ll,ll> p1, p2, p3, p4;
    while (true) {
        // Generate first segment
        if (axis1) {
            bool vert = rnd.next(0,1) == 1;
            if (vert) {
                ll x = rnd.next(-B, B);
                ll y1 = rnd.next(-B, B), y2 = rnd.next(-B, B);
                if (y1 == y2) y2 = y1 + 1;
                p1 = {x, y1}; p2 = {x, y2};
            } else {
                ll y = rnd.next(-B, B);
                ll x1 = rnd.next(-B, B), x2 = rnd.next(-B, B);
                if (x1 == x2) x2 = x1 + 1;
                p1 = {x1, y}; p2 = {x2, y};
            }
        } else {
            do {
                p1 = { rnd.next(-B, B), rnd.next(-B, B) };
                p2 = { rnd.next(-B, B), rnd.next(-B, B) };
            } while (p1 == p2);
        }
        // Generate second segment
        if (axis2) {
            bool vert = rnd.next(0,1) == 1;
            if (vert) {
                ll x = rnd.next(-B, B);
                ll y1 = rnd.next(-B, B), y2 = rnd.next(-B, B);
                if (y1 == y2) y2 = y1 + ((y1+1<=B)?1:-1);
                p3 = {x, y1}; p4 = {x, y2};
            } else {
                ll y = rnd.next(-B, B);
                ll x1 = rnd.next(-B, B), x2 = rnd.next(-B, B);
                if (x1 == x2) x2 = x1 + ((x1+1<=B)?1:-1);
                p3 = {x1, y}; p4 = {x2, y};
            }
        } else {
            do {
                p3 = { rnd.next(-B, B), rnd.next(-B, B) };
                p4 = { rnd.next(-B, B), rnd.next(-B, B) };
            } while (p3 == p4);
        }
        // No three collinear among the four points
        vector<pair<ll,ll>> pts = {p1,p2,p3,p4};
        bool ok = true;
        for (int i = 0; i < 4 && ok; i++)
            for (int j = i+1; j < 4 && ok; j++)
                for (int k = j+1; k < 4; k++)
                    if (orient(pts[i], pts[j], pts[k]) == 0)
                        ok = false;
        if (!ok) continue;
        // Check intersection property
        bool isect = properIntersect(p1,p2,p3,p4);
        if (isect == wantIntersect) break;
    }
    // Output
    println(p1.first, p1.second, p2.first, p2.second);
    println(p3.first, p3.second, p4.first, p4.second);
    return 0;
}

#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<string> types = {
        "cross",
        "endpoint",
        "collinear_overlap",
        "collinear_touch",
        "collinear_no",
        "parallel_no",
        "vertical_horizontal",
        "vertical_cross",
        "large_coords"
    };
    string tp = rnd.any(types);

    // candidate direction vectors for non-degenerate lines
    vector<pair<int,int>> dirs = {
        {1,0},{0,1},{1,1},{1,-1},
        {2,1},{1,2},{-1,1},{2,-1},{-2,1}
    };

    int x1,y1,x2,y2,x3,y3,x4,y4;

    if (tp == "cross") {
        // two segments crossing at an interior point
        int px = rnd.next(-10, 10), py = rnd.next(-10, 10);
        auto d1 = rnd.any(dirs), d2 = rnd.any(dirs);
        while ((ll)d1.first * d2.second == (ll)d1.second * d2.first)
            d2 = rnd.any(dirs);
        int a1 = rnd.next(1,5), b1 = rnd.next(1,5);
        int a2 = rnd.next(1,5), b2 = rnd.next(1,5);
        x1 = px + d1.first * a1;  y1 = py + d1.second * a1;
        x2 = px - d1.first * b1;  y2 = py - d1.second * b1;
        x3 = px + d2.first * a2;  y3 = py + d2.second * a2;
        x4 = px - d2.first * b2;  y4 = py - d2.second * b2;
    }
    else if (tp == "endpoint") {
        // intersection exactly at one endpoint
        do {
            x1 = rnd.next(-10,10); y1 = rnd.next(-10,10);
            x2 = rnd.next(-10,10); y2 = rnd.next(-10,10);
        } while (x1==x2 && y1==y2);
        bool useFirst = rnd.next(0,1);
        int px = useFirst ? x1 : x2;
        int py = useFirst ? y1 : y2;
        int ox = useFirst ? x2 : x1;
        int oy = useFirst ? y2 : y1;
        // choose a point not collinear and not equal
        do {
            x3 = rnd.next(-10,10); y3 = rnd.next(-10,10);
        } while ((x3==px && y3==py)
              || (ll)(ox-px)*(y3-py) == (ll)(oy-py)*(x3-px));
        // segment2 = (px,py)-(x3,y3)
        x4 = x3; y4 = y3;
        x3 = px; y3 = py;
    }
    else if (tp == "collinear_overlap") {
        // infinite overlap (one inside another)
        vector<int> v;
        while ((int)v.size() < 4) {
            int t = rnd.next(-5,5);
            if (find(v.begin(), v.end(), t) == v.end())
                v.push_back(t);
        }
        sort(v.begin(), v.end());
        auto dir = rnd.any(dirs);
        int dx = dir.first, dy = dir.second;
        // seg1: [v0, v3], seg2: [v1, v2]
        x1 = v[0]*dx; y1 = v[0]*dy;
        x2 = v[3]*dx; y2 = v[3]*dy;
        x3 = v[1]*dx; y3 = v[1]*dy;
        x4 = v[2]*dx; y4 = v[2]*dy;
    }
    else if (tp == "collinear_touch") {
        // touch at exactly one endpoint
        vector<int> v;
        while ((int)v.size() < 3) {
            int t = rnd.next(-5,5);
            if (find(v.begin(), v.end(), t) == v.end())
                v.push_back(t);
        }
        sort(v.begin(), v.end());
        auto dir = rnd.any(dirs);
        int dx = dir.first, dy = dir.second;
        // seg1: [v0, v1], seg2: [v1, v2]
        x1 = v[0]*dx; y1 = v[0]*dy;
        x2 = v[1]*dx; y2 = v[1]*dy;
        x3 = v[1]*dx; y3 = v[1]*dy;
        x4 = v[2]*dx; y4 = v[2]*dy;
    }
    else if (tp == "collinear_no") {
        // collinear but disjoint
        vector<int> v;
        while ((int)v.size() < 4) {
            int t = rnd.next(-5,5);
            if (find(v.begin(), v.end(), t) == v.end())
                v.push_back(t);
        }
        sort(v.begin(), v.end());
        auto dir = rnd.any(dirs);
        int dx = dir.first, dy = dir.second;
        // seg1: [v0,v1], seg2: [v2,v3], with v1 < v2
        x1 = v[0]*dx; y1 = v[0]*dy;
        x2 = v[1]*dx; y2 = v[1]*dy;
        x3 = v[2]*dx; y3 = v[2]*dy;
        x4 = v[3]*dx; y4 = v[3]*dy;
    }
    else if (tp == "parallel_no") {
        // parallel, non-touching
        vector<int> u;
        while ((int)u.size() < 2) {
            int t = rnd.next(-5,5);
            if (find(u.begin(), u.end(), t) == u.end())
                u.push_back(t);
        }
        vector<int> v;
        while ((int)v.size() < 2) {
            int t = rnd.next(-5,5);
            if (find(v.begin(), v.end(), t) == v.end())
                v.push_back(t);
        }
        auto dir = rnd.any(dirs);
        int dx = dir.first, dy = dir.second;
        // perpendicular offset
        int px = -dy, py = dx;
        int k = rnd.next(1,5);
        // seg1 at offset 0, seg2 at offset k*(perp)
        x1 = u[0]*dx;             y1 = u[0]*dy;
        x2 = u[1]*dx;             y2 = u[1]*dy;
        x3 = v[0]*dx + k*px;      y3 = v[0]*dy + k*py;
        x4 = v[1]*dx + k*px;      y4 = v[1]*dy + k*py;
    }
    else if (tp == "vertical_horizontal") {
        // perpendicular vertical/horizontal
        int c = rnd.next(-10,10), d = rnd.next(-10,10);
        x1 = c;   y1 = d-2;
        x2 = c;   y2 = d+2;
        x3 = c-2; y3 = d;
        x4 = c+2; y4 = d;
    }
    else if (tp == "vertical_cross") {
        // vertical segment & slanted segment crossing in interior
        int u0,u1;
        do {
            u0 = rnd.next(-5,5);
            u1 = rnd.next(-5,5);
        } while (u1 - u0 < 2);
        int a = rnd.next(-5,5);
        int pm = rnd.next(u0+1, u1-1);
        // vertical segment [(a,u0)-(a,u1)]
        x1 = a; y1 = u0;
        x2 = a; y2 = u1;
        // slanted line through (a,pm)
        pair<int,int> dir2 = rnd.any(vector<pair<int,int>>{{1,1},{1,-1}});
        int d1 = rnd.next(1,5), d2 = rnd.next(1,5);
        x3 = a + dir2.first * d1;
        y3 = pm + dir2.second * d1;
        x4 = a - dir2.first * d2;
        y4 = pm - dir2.second * d2;
    }
    else { // large_coords
        // like cross but with large coordinates
        int margin = 1000;
        int px = rnd.next(-1000000+margin, 1000000-margin);
        int py = rnd.next(-1000000+margin, 1000000-margin);
        auto d1 = rnd.any(dirs), d2 = rnd.any(dirs);
        while ((ll)d1.first * d2.second == (ll)d1.second * d2.first)
            d2 = rnd.any(dirs);
        int a1 = rnd.next(1,500), b1 = rnd.next(1,500);
        int a2 = rnd.next(1,500), b2 = rnd.next(1,500);
        x1 = px + d1.first * a1;  y1 = py + d1.second * a1;
        x2 = px - d1.first * b1;  y2 = py - d1.second * b1;
        x3 = px + d2.first * a2;  y3 = py + d2.second * a2;
        x4 = px - d2.first * b2;  y4 = py - d2.second * b2;
    }

    // Output one test
    println(x1, y1, x2, y2);
    println(x3, y3, x4, y4);
    return 0;
}

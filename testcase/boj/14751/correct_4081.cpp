#include <bits/stdc++.h>
using namespace std;
#define double long double
struct Line {
    mutable double k, m, p;
    int idx;
    bool operator<(const Line& o) const { return k < o.k; }
    bool operator<(double x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
    // (for doubles, use inf = 1/.0, div(a,b) = a/b)
    const double inf = numeric_limits<double>::infinity();
    double div(double a, double b) { // floored division
        return a / b;
    }
    bool isect(iterator x, iterator y) {
        if (y == end()) return x->p = inf, 0;
        if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
        else x->p = div(y->m - x->m, x->k - y->k);
        return x->p >= y->p;
    }
    void add(double k, double m, int idx) {
        // printf("added %lf %lf %d\n", k, m, idx);
        auto z = insert({k, m, 0, idx}), y = z++, x = y;
        while (isect(y, z)) z = erase(z);
        if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
        while ((y = x) != begin() && (--x)->p >= y->p)
            isect(x, erase(y));
    }
    double query(double x) {
        assert(!empty());
        auto l = *lower_bound(x);
        return l.idx;
    }
};
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int max_y, min_y;
    cin >> max_y >> min_y;
    
    int n;
    cin >> n;
    LineContainer lc;
    for(int i=0; i<n; i++) {
        int hi_x, lo_x;
        cin >> hi_x >> lo_x;
        double k = (hi_x - lo_x) / (double)(max_y - min_y);
        double m = -hi_x;
        lc.add(k, m, i+1);
    }
    // for(auto it: lc) {
    //     printf("%lf %lf %lf %d\n", it.k, it.m, it.p, it.idx);
    // }
    int q;
    cin >> q;
    for(int i=0; i<q; i++) {
        double y_db;
        cin >> y_db;
        double y = max_y - y_db;
        // printf("query at %lf, raw was %lf\n", y, y_db);
        int x = lc.query(y - 1e-9);
        cout << x << '\n';
    }
}

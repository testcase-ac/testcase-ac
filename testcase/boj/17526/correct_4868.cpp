#include <bits/stdc++.h>
using namespace std;
#define int long long
struct Line {
    mutable int k, m, p;
    bool operator<(const Line& o) const { return k < o.k; }
    bool operator<(int x) const { return p < x; }
};
struct LineContainer : multiset<Line, less<>> {
    static const int inf = LLONG_MAX;
    int div(int a, int b) { return a / b - ((a ^ b) < 0 && a % b); }
    bool isect(iterator x, iterator y) {
        if(y == end()) return x->p = inf, 0;
        if(x->k == y->k) x->p = x->m > y->m ? inf: -inf;
        else x->p = div(y->m - x->m, x->k - y->k);
        return x->p >= y->p;
    }

    void add(int k, int m) {
        k *= -1, m *= -1;
        auto z = insert({k, m, 0}), y = z++, x = y;
        while(isect(y, z)) z = erase(z);
        if(x != begin() && isect(--x, y)) isect(x, y = erase(y));
        while((y = x) != begin() && (--x)->p >= y->p)
            isect(x, erase(y));
    }
    int query(int x) {
        assert(!empty());
        auto l = *lower_bound(x);
        return -(l.k * x + l.m);
    }
};
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N;
    cin >> N;
    vector<int> D(N-1), T(N-1), P(N-1);
    for(int i=0; i<N-1; i++) {
        cin >> D[i];
    }
    for(int i=0; i<N-1; i++) {
        cin >> P[i] >> T[i];
    }
    LineContainer lc;
    lc.add(T[0], P[0]);
    int acc = 0;
    for(int i=1; i<N-1; i++) {
        acc += D[i-1];
        int v = lc.query(acc);
        lc.add(T[i], P[i] + v - T[i] * acc);
    }
    acc += D[N-2];
    cout << lc.query(acc);
}

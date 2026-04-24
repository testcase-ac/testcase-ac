#include <bits/stdc++.h>
using namespace std;
#define int long long
struct point {
    int x, y, idx;
    explicit point(int x=0, int y=0) : x(x), y(y) {}
    void read() {cin >> x >> y;}
    point operator* (int d) {return point(x*d, y*d);}
    point operator-(point p) {return point(x-p.x, y-p.y);}
    int cross(point p) {return x*p.y - y*p.x;}
    int cross(point a, point b) {
        return (a-*this).cross(b-*this);
    }
};
int sgn(int x) {return (x > 0) - (x < 0);}
bool solve() {
    int N;
    cin >> N;
    vector<point> arr(N);
    vector<int> par(N);
    iota(par.begin(), par.end(), 0);
    function<int(int)> f = [&](int x) {
        return x == par[x] ? x : (par[x] = f(par[x]));
    };
    auto join = [&](int a, int b) {
        a = f(a), b = f(b);
        if(a != b) {
            par[b] = a;
        }
    };
    int nxt = 0;
    for(auto &i: arr) {
        i.read();
        i.idx = nxt++;
    }
    vector<pair<point, point>> lines;
    sort(arr.begin(), arr.end(), [&](point a, point b) {return tie(a.x, a.y) < tie(b.x, b.y);});
    for(int i=0, j=0; i<N; i=j) {
        while(j < N && arr[i].x == arr[j].x) {
            j++;
        }
        if((j-i) % 2) {
            return 0;
        }
        for(int k=i; k<j; k+=2) {
            lines.emplace_back(arr[k], arr[k+1]);
            join(arr[k].idx, arr[k+1].idx);
        }
    }
    sort(arr.begin(), arr.end(), [&](point a, point b) {return tie(a.y, a.x) < tie(b.y, b.x);});
    for(int i=0, j=0; i<N; i=j) {
        while(j < N && arr[i].y == arr[j].y) {
            j++;
        }
        if((j-i) % 2) {
            return 0;
        }
        for(int k=i; k<j; k+=2) {
            lines.emplace_back(arr[k], arr[k+1]);
            join(arr[k].idx, arr[k+1].idx);
        }
    }
    for(int i=1; i<N; i++) {
        if(f(i) != f(0)) {
            return 0;
        }
    }
    for(int i=0; i<lines.size(); i++) {
        for(int j=i+1; j<lines.size(); j++) {
            auto l1 = lines[i], l2 = lines[j];
            auto a = l1.first, b = l1.second, c = l2.first, d = l2.second;
            auto oa = c.cross(d, a), ob = c.cross(d, b), oc = a.cross(b, c), od = a.cross(b, d);
            if(sgn(oa) * sgn(ob) < 0 && sgn(oc) * sgn(od) < 0) {
                return 0;
            }
        }
    }
    return 1;
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin >> T;
    while(T--) {
        cout << (solve() ? "YES" : "NO") << '\n';
    }
}

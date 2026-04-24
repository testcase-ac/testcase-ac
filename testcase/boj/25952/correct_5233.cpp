#include <bits/stdc++.h>
using namespace std;
#define int long long
struct point {
    int x, y;
};
const int BOUND = 1000;
const int MX = 1e5 +1;
int NC2[MX];
inline int compress(int s1, int s2) {
    assert(s1 < 70000 && s2 < 70000);
    if(s2 > s1) {
        swap(s1, s2);
    }
    return s1 * 70001 + s2;
}
int32_t main() {
    for(int i=2; i<MX; i++) {
        NC2[i] = i * (i-1) / 2;
    }
    cin.tie(0)->sync_with_stdio(0);
    int N;
    cin >> N;
    vector<point> v(N);
    map<int, int> mpx, mpy;

    for(int i=0; i<N; i++) {
        cin >> v[i].x >> v[i].y;
        mpx[v[i].x] = 0;
        mpy[v[i].y] = 0;
    }

    int nxt = 0;
    for(auto &[k, v]: mpx) {
        v = nxt++;
    }
    nxt = 0;
    for(auto &[k, v]: mpy) {
        v = nxt++;
    }
    for(int i=0; i<N; i++) {
        v[i].x = mpx[v[i].x];
        v[i].y = mpy[v[i].y];
    }

    sort(v.begin(), v.end(), [](auto a, auto b){
        return tie(a.y, a.x) < tie(b.y, b.x);
    });

    vector<int> yarr(70001);
    vector<int> is_above(70001);
    vector<vector<int>> xbuk(70001);
    for(int i=0; i<N; i++) {
        xbuk[v[i].x].push_back(v[i].y);
    }
    int ans = 0;
    vector<int> segs;
    map<int, int> mp;
    for(int i=0, j=0; i<N; i=j) {
        while(j < N && v[i].y == v[j].y) {
            j++;
        }
        if(j-i > BOUND) {
            is_above[v[i].y] = 1;
            fill(yarr.begin(), yarr.end(), 0ll);
            for(int t=i; t<j; t++) {
                for(int y: xbuk[v[t].x]) {
                    if(y > v[i].y || (y < v[i].y && !is_above[y])) {
                        yarr[y]++;
                    }
                }
            }
            for(int t: yarr) {
                ans += NC2[t];
            }
        } else {
            for(int t1=i; t1<j; t1++) {
                for(int t2=t1+1; t2<j; t2++) {
                    int cp = compress(v[t1].x, v[t2].x);
                    mp[cp]++;
                }
            }
        }
    }
    for(auto [k, v]: mp) {
        ans += NC2[v];
    }
    cout << ans;
}

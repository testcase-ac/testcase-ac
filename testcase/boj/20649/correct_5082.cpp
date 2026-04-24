#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
#define int long long
struct cow {
    char dir;
    int x, y, i;
    void read() { cin >> dir >> x >> y; }
};
struct comp {
    int stopped, stopper, t, anotherT;
};
int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    vector<cow> north, east;
    for(int i = 0; i < n; i++) {
        cow c;
        c.i = i;
        c.read();
        if(c.dir == 'N')
            north.push_back(c);
        else
            east.push_back(c);
    }

    vector<comp> comps;
    for(auto& cow_n: north) {
        for(auto& cow_e: east) {
            int t1 = cow_e.y - cow_n.y;  // n충돌
            int t2 = cow_n.x - cow_e.x;  // e충돌
            if(t1 > 0 && t2 > 0) {
                if(t1 > t2) {
                    comps.push_back({cow_n.i, cow_e.i, t1, t2});
                } else if(t1 < t2) {
                    comps.push_back({cow_e.i, cow_n.i, t2, t1});
                }
            }
        }
    }
    
    sort(comps.begin(), comps.end(), [](comp a, comp b) { return a.t < b.t; });
    vector<int> stopped_time(n + 1);
    vector<vector<int>> edges(n + 1);
    for(auto& c: comps) {
        if((!stopped_time[c.stopper] || stopped_time[c.stopper] >= c.anotherT) && !stopped_time[c.stopped]) {
            stopped_time[c.stopped] = c.t;
            edges[c.stopper + 1].push_back(c.stopped + 1);
        }
    }
    function<int(int, int)> dfs = [&](int i, int p) {
        int ret = 1;
        for(auto& e: edges[i]) {
            if(e == p) continue;
            ret += dfs(e, i);
        }
        return ret;
    };

    for(int i = 1; i <= n; i++) {
        cout << dfs(i, -1) - 1 << '\n';
    }
}

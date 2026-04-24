#include <bits/stdc++.h>
using namespace std;
#define int long long
struct rect {
    int x1, y1, x2, y2;
    void read() {
        cin >> x1 >> y1 >> x2 >> y2;
    }
};
int solve() {
    int N;
    cin >> N;
    vector<int> xs, ys;
    vector<rect> rects(N);
    for(auto &r : rects) {
        r.read();
        xs.push_back(r.x1);
        xs.push_back(r.x2);
        ys.push_back(r.y1);
        ys.push_back(r.y2);
    }
    sort(xs.begin(), xs.end());
    sort(ys.begin(), ys.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());
    vector<vector<rect>> events(xs.size());
    for(auto &r : rects) {
        r.x1 = lower_bound(xs.begin(), xs.end(), r.x1) - xs.begin();
        r.x2 = lower_bound(xs.begin(), xs.end(), r.x2) - xs.begin();
        r.y1 = lower_bound(ys.begin(), ys.end(), r.y1) - ys.begin();
        r.y2 = lower_bound(ys.begin(), ys.end(), r.y2) - ys.begin();
        events[r.x1].push_back(r);
        events[r.x2].push_back(r);
    }
    vector<int> counter(ys.size());
    int ans = 0;
    for(int i=0; i<xs.size()-1; i++) {
        auto &ev = events[i];
        for(auto &r : ev) {
            if(r.x1 == i) {
                for(int j=r.y1; j<r.y2; j++) {
                    counter[j]++;
                }
            } else {
                for(int j=r.y1; j<r.y2; j++) {
                    counter[j]--;
                }
            }
        }
        int xlen = xs[i+1] - xs[i], ysum = 0;
        for(int j=0; j<ys.size()-1; j++) {
            if(counter[j] > 0) {
                ysum += ys[j+1] - ys[j];
            }
        }
        ans += xlen * ysum;
    }
    return ans;
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin >> T;
    while(T--) {
        cout << solve() << '\n';
    }
}

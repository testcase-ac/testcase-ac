#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 2e5+4;
vector<int> adj[MX];
map<int, int> mps[MX];
int dfs(int i, int p, int h) {
    int l = -1, r = -1;
    for(int a: adj[i]) {
        if(a == p) continue;
        if(l == -1) {
            l = a;
        } else if(r == -1) {
            r = a;
        }
    }
    int lh = h, rh = h, ans = 0;
    if(l != -1) {
        ans += dfs(l, i, h+1);
        lh = mps[l].rbegin()->first;
    }
    if(r != -1) {
        ans += dfs(r, i, h+1);
        rh = mps[r].rbegin()->first;
    }
    while(lh+1< rh) {
        ans += mps[r].rbegin()->second;
        mps[r].erase(prev(mps[r].end()));
        rh--;
    }
    while(rh+1 < lh) {
        ans += mps[l].rbegin()->second;
        mps[l].erase(prev(mps[l].end()));
        lh--;
    }
    if(l == -1 && r == -1) {
        // do nothing
    } else if(lh == h) {
        swap(mps[r], mps[i]);
    } else if(rh == h) {
        swap(mps[l], mps[i]);
    } else if(mps[l].size() > mps[r].size()) {
        swap(mps[l], mps[i]);
        for(auto &[th, tv]: mps[r]) {
            mps[i][th] += tv;
        }
    } else {
        swap(mps[r], mps[i]);
        for(auto &[th, tv]: mps[l]) {
            mps[i][th] += tv;
        }
    }
    mps[i][h] = 1;
    return ans;
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N;
    cin >> N;
    for(int i=0; i<N-1; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    int ans = dfs(1, 0, 0);
    cout << ans;

}

#include <bits/stdc++.h>
using namespace std;

char arr[512][513];
void solve() {
    int N;
    cin >> N;
    for(int i=0; i<N; i++) {
        cin >> arr[i];
    }
    vector<int> cur(N);
    for(int i=0; i<N; i++) {
        cur[i] = i;
    }
    vector<int> ans;
    int len = 1 + (int)log2(N);
    vector<vector<int>> adj(N);
    while(ans.size() < len) {
        for(int i=0; i<N; i++) {
            adj[i].clear();
        }
        int mx = cur[0];
        for(int t1: cur) {
            for(int t2: cur) {
                if(arr[t1][t2] == 'W') {
                    adj[t1].push_back(t2);
                }
            }
            if(adj[t1].size() > adj[mx].size()) {
                mx = t1;
            }
        }
        ans.push_back(mx);
        cur = adj[mx];
    }
    for(int t: ans) {
        cout << t+1 << ' ';
    }
    cout << '\n';
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin >> T;
    while(T--) {
        solve();
    }
}

#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 1e6 + 1;
int dist[MX], prv[MX];
void solve(int n) {
    if(n == 1) {
        cout << "1\n";
        return;
    }
    memset(dist, -1, sizeof(dist));
    memset(prv, -1, sizeof(prv));
    queue<int> q;
    q.push(1);
    dist[1] = 0;
    auto visit = [&](int a, int i) {
        if(dist[a] == -1) {
            dist[a] = dist[i] + 1;
            prv[a] = i;
            q.push(a);
        }
    };
    while(!q.empty()) {
        int u = q.front();
        q.pop();
        visit((u * 10) % n, u);
        visit((u * 10 + 1) % n, u);
    }
    if(dist[0] == -1) {
        cout << "BRAK" << '\n';
        return;
    }
    string ans;
    int u = 0;
    while(prv[u] != -1) {
        ans += ((prv[u] * 10 + 1) % n == u) ? '1' : '0';
        u = prv[u];
    }
    ans.push_back('1');
    reverse(ans.begin(), ans.end());
    cout << ans << '\n';
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin >> T;
    while(T--) {
        int n;
        cin >> n;
        solve(n);
    }
}

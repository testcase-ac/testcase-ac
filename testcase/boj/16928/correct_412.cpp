#include <bits/stdc++.h>
using namespace std;
#define int long long
int seen[101];
int edge[101];
int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    for(int i = 0; i < n + m; i++) {
        int a, b;
        cin >> a >> b;
        edge[a] = b;
    }
    queue<int> que;
    que.push(1);
    int ans = 0;
    while(que.size()) {
        int s = que.size();
        while(s--) {
            int cur = que.front();
            que.pop();

            for(int nxt = cur + 1; nxt <= cur + 6; nxt++) {
                if(nxt == 100) {
                    return !(cout << ans + 1);
                }
                int nxt_real = edge[nxt] ? edge[nxt] : nxt;
                if(seen[nxt_real]) continue;
                seen[nxt_real] = 1;
                que.push(nxt_real);
            }
        }
        ans++;
    }
}

#include <bits/stdc++.h>
using namespace std;
#define int long long
int solve() {
    int N;
    cin >> N;
    assert(N >= 2);
    vector<int> A(N+1), vis(N+1);
    for (int i = 1; i <= N; i++) {
        cin >> A[i];
    }
    int cur = 1, cnt = 0;
    while(true) {
        vis[cur] = 1;
        cur = A[cur];
        cnt++;
        if(cur == N) {
            return cnt;
        } else if(vis[cur]) {
            return 0;
        }
    }
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin >> T;
    while(T--) {
        cout << solve() << '\n';
    }
}
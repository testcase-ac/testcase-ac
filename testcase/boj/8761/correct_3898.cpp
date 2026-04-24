#include <bits/stdc++.h>
using namespace std;
#define int long long

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin >> T;
    while(T--) {
        int N;
        cin >> N;
        vector<int> v(N);
        int ans = INT_MAX;
        for(int i=0; i<N; i++) {
            cin >> v[i];
            if(v[i] == 1) continue;
            ans = min(ans, max(i, N-i-1) * 2);
        }
        cout << ans << '\n';
    }
}

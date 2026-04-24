#include <bits/stdc++.h>
using namespace std;

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, C, B;
    cin >> N >> C >> B;
    vector<int> fixed(N+1);
    for(int i=0; i<B; i++) {
        int t;
        cin >> t;
        fixed[t] = 1;
    }
    vector<int> ans(N+1);
    int cnt = C, start = 2;
    if(cnt&1) {
        ans[1] = 1;
        cnt--;
        start++;
    }
    for(int i=start; i<=N; i++) {
        if(fixed[i]) {
            continue;
        }
        if(cnt) {
            cnt -= 2;
            ans[i] = 1;
            i++;
        } 
    }
    for(int i=1; i<=N; i++)
        cout << ans[i];
}

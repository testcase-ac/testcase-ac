#include <bits/stdc++.h>
using namespace std;
#define int long long
#define all(x) x.begin(), x.end()
#define rep(i, N) for(int i=0; i<N; i++)
const int MX = 1e6+2;
int seg[MX*2];
void update(int i, int x) {
    i += MX;
    seg[i] += x;
    while(i /= 2) {
        seg[i] = seg[i*2] + seg[i*2+1];
    }
}
int query(int l, int r) {
    l += MX, r += MX;
    int res = 0;
    while(l < r) {
        if(l&1) res += seg[l++];
        if(r&1) res += seg[--r];
        l /= 2, r /= 2;
    }
    return res;
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N;
    cin >> N;
    vector<int> A(N), B(N);
    for(int i=0; i<N; i++) {
        cin >> A[i];
    }
    for(int i=0; i<N; i++) {
        cin >> B[i];
    }

    vector<int> idx(N);
    iota(all(idx), 0);
    sort(all(idx), [&](int a, int b) {return A[a] < A[b];});
    vector<int> ta(N), tb(N);
    for(int i=0; i<N; i++) {
        ta[i] = A[idx[i]];
        tb[i] = B[idx[i]];
    }
    vector<int> dp(N), dp2(N);
    int lst = N;
    for(int i=N-1; i>=0; i--) {
        dp[i] = query(tb[i]+1, MX);
        // printf("dp %d = %d\n", i, dp[i]);
        if(i && ta[i-1] != ta[i]) {
            for(int k=i; k<lst; k++) {
                // printf("update at k = %d, tb[k] = %d\n", k, tb[k]);
                update(tb[k], 1);
            }
            lst = i;
        }
    }
    memset(seg, 0, sizeof seg);
    lst = N;
    int ans = 0;
    for(int i=N-1; i>=0; i--) {
        dp2[i] = query(tb[i]+1, MX);
        // printf("dp2 %d = %d\n", i, dp2[i]);
        ans += dp2[i];
        if(i && ta[i-1] != ta[i]) {
            for(int k=i; k<lst; k++) {
                update(tb[k], dp[k]);
            }
            lst = i;
        }
    }
    cout << ans;
}

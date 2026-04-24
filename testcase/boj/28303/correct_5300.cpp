#include <bits/stdc++.h>
using namespace std;
#define int long long
int N, K;

int solve(vector<int> a) {
    vector<int> diffed = a, mn(a.size());
    for(int i=0; i<N; i++) {
        diffed[i] += i * K;
    }
    mn.back() = diffed.back();
    for(int i=N-2; i>=0; i--) {
        mn[i] = min(mn[i+1], diffed[i]);
    }
    int ans = INT_MIN;
    for(int i=0; i<N-1; i++) {
        // printf("at i = %lld, a = %lld, mn = %lld\n", i, a[i], mn[i+1]);
        ans = max(ans, a[i] - mn[i+1] + i * K);
    }
    return ans;
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> N >> K;
    vector<int> A(N);
    for(int i=0; i<N; i++) {
        cin >> A[i];
    }
    int ans = solve(A);
    reverse(A.begin(), A.end());
    ans = max(ans, solve(A));
    cout << ans;
}

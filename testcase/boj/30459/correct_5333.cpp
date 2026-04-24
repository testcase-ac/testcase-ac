#include <bits/stdc++.h>
using namespace std;
#define int long long

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, M, R;
    cin >> N >> M >> R;
    vector<int> A(N), B(M);
    for(int i=0; i<N; i++) {
        cin >> A[i];
    }
    for(int j=0; j<M; j++) {
        cin >> B[j];
    }
    sort(A.begin(), A.end());
    sort(B.begin(), B.end(), greater<int>());
    int ans = -1;
    for(int i=0; i<N; i++) {
        for(int j=i+1; j<N; j++) {
            int d = A[j] - A[i];
            auto it = lower_bound(B.begin(), B.end(), 2*R/d, greater<int>());
            if(it != B.end()) {
                ans = max(ans, (*it) * d);
            }
        }
    }
    if(ans == -1) {
        cout << -1 << '\n';
    } else {
        cout << fixed << setprecision(1) << ans / 2.0 << '\n';
    }
}

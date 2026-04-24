#include <bits/stdc++.h>
using namespace std;
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N;
    cin >> N;
    vector<int> A(6);
    for(int i=0; i<6; i++) cin >> A[i];
    int T, P;
    cin >> T >> P;
    int ans = 0;
    for(int i=0; i<6; i++) {
        ans += (A[i] + T - 1) / T;
    }
    cout << ans << '\n';
    cout << N / P << ' ' << N % P << '\n';
}

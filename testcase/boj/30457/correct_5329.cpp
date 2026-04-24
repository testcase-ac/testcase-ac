#include <bits/stdc++.h>
using namespace std;

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N;
    cin >> N;
    vector<int> A(N);
    for(int i=0; i<N; i++) {
        cin >> A[i];
    }
    sort(A.begin(), A.end());
    int ans = 0;
    for(int i=0, j=0; i<N; i=j) {
        while(j < N && A[i] == A[j]) j++;

        ans += min(j-i, 2);
    }
    cout << ans;
}

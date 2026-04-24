#include <bits/stdc++.h>
using namespace std;
#define int long long

int32_t main() {
    int N;
    cin >> N;
    vector<int> A(N);
    int sm = 0;
    for(int i=0; i<N; i++) {
        cin >> A[i];
        sm += A[i];
    }
    int h = sm / N, t = sm % N;
    sort(A.begin(), A.end(), greater<int>());
    int ans = 0;
    for(int i=0; i<t; i++) {
        ans += max(A[i] - (h+1), 0ll);
    }
    for(int i=t; i<N; i++) {
        ans += max(A[i] - h, 0ll);
    }
    cout << ans;
}

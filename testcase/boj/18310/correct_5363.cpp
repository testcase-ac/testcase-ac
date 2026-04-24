#include <bits/stdc++.h>
using namespace std;
#define int long long

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N;
    cin >> N;
    vector<int> a(N);
    for(int i = 0; i < N; i++) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    cout << a[(N-1) / 2];
}

#include <bits/stdc++.h>
using namespace std;
#define int long long
int arr[10000];
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, K;
    cin >> N >> K;
    for(int i=0; i<N; i++) {
        cin >> arr[i];
    }
    sort(arr, arr+N);
    vector<int> diff;
    for(int i=0; i<N-1; i++) {
        diff.push_back(arr[i+1] - arr[i]);
    }
    sort(diff.begin(), diff.end());
    int cnt = N-K;
    int ans = 0;
    for(int i=0; i<cnt; i++) {
        ans += diff[i];
    }
    cout << ans;
}

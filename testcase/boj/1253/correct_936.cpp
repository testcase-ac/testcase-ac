#include <bits/stdc++.h>
using namespace std;
#define int long long
int arr[2000], N, ans;
void solve(int t) {
    int target = arr[t];
    int l = 0, r = N-1;
    while(l < r) {
        if(l == t) {
            l++;
            continue;
        }
        if(r == t) {
            r--;
            continue;
        }
        int sum = arr[l] + arr[r];
        if(sum == target) {
            ans++;
            return;
        } else if(sum < target) {
            l++;
        } else {
            r--;
        }
    }
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> N;
    for(int i=0; i<N; i++) {
        cin >> arr[i];
    }
    sort(arr, arr+N);
    for(int i=0; i<N; i++) {
        solve(i);
    }
    cout << ans << '\n';
}

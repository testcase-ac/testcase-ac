#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 5e5+5;
int arr[MX], acc[MX], seg[MX*2], N;

int mx_query(int l, int r) {
    l += N, r += N;
    int res = seg[l];
    while(l < r) {
        if(l&1) {
            if(arr[seg[l]] > arr[res]) {
                res = seg[l];
            }
            l++;
        }
        if(r&1) {
            r--;
            if(arr[seg[r]] > arr[res]) {
                res = seg[r];
            }
        }
        l /= 2, r /= 2;
    }
    return res;
}
int solve(int l, int r) {
    if(l == r) {
        return arr[l];
    }
    if(l > r) {
        return 0;
    } 
    int mx_idx = mx_query(l, r+1);
    int lft = solve(l, mx_idx-1);
    int rht = solve(mx_idx+1, r);
    int lft_sum = acc[mx_idx-1] - acc[l-1], rht_sum = acc[r] - acc[mx_idx];
    lft = max(lft, arr[mx_idx] - lft_sum);
    rht = max(rht, arr[mx_idx] - rht_sum);
    return min(lft, rht);
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> N;
    for(int i=0; i<N; i++) {
        cin >> arr[i];
    }
    int mx_i = max_element(arr, arr+N) - arr;
    rotate(arr, arr+mx_i, arr+N);
    for(int i=1; i<N; i++) {
        seg[i+N] = i;
        acc[i] = arr[i] + acc[i-1];
    }
    for(int i=N-1; i>=1; i--) {
        seg[i] = arr[seg[i*2]] < arr[seg[i*2+1]] ? seg[i*2+1] : seg[i*2];
    }
    int ans = solve(1, N-1);
    int sum = acc[N-1] - acc[0];
    ans = max(ans, arr[0] - sum);
    cout << ans;
}

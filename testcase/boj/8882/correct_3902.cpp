#include <bits/stdc++.h>
using namespace std;
#define int long long
int N, K;
int arr[1000000];
bool solve(int t) {
    int cnt = 0;
    for(int i = 0; i < 2 * N * K - 1; i++) {
        if(arr[i + 1] - arr[i] <= t) {
            cnt += 2 * K - 2;
            i++;
        } else {
            cnt--;
            if(cnt < 0) {
                return false;
            }
        }
    }
    return true;
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> N >> K;
    for(int i = 0; i < 2 * N * K; i++) {
        cin >> arr[i];
    }
    sort(arr, arr + 2 * N * K);
    int l = 0, r = 1e9 + 1;
    while(l < r) {
        int m = (l + r) / 2;
        if(solve(m)) {
            r = m;
        } else {
            l = m + 1;
        }
    }
    cout << l;
}

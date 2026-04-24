#include <bits/stdc++.h>
using namespace std;

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if(!arr[i]) continue;
        ans++;
        for(int j=0; j<3 && i+j<n; j++) {
            arr[i+j] = !arr[i+j];
        }
    }
    cout << ans;
}


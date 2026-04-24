#include <bits/stdc++.h>
using namespace std;
#define int long long

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N;
    cin >> N;
    vector<int> arr(N);
    for(int i = 0; i < N; i++) {
        cin >> arr[i];
    }
    int cnt = N;
    for(int i = N - 1; i >= 0; i--) {
        if(arr[i] == cnt) {
            cnt--;
        }
    }
    cout << cnt << '\n';
}

#include <bits/stdc++.h>
using namespace std;
#define int long long
int32_t main() {
    int N;
    cin >> N;
    int a = 0, b = 0;
    for(int i=0; i<N; i++) {
        int t;
        cin >> t;
        if(i == 0) {
            a += t;
        } else if(i == 1) {
            b += t;
        } else if(a <= b) {
            a += t;
        } else {
            b += t;
        }
    }
    int x = abs(a - b);
    vector<int> arr = {100,50,20,10,5,2,1};
    int ans = 0;
    for(int t: arr) {
        int cnt = x / t;
        ans += cnt;
        x %= t;
    }
    cout << ans;
}

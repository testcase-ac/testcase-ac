#include <bits/stdc++.h>
using namespace std;
#define int long long

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    if(n < 10) {
        return !(cout << n+1);
    }
    if(n == 10) {
        return !(cout << n);
    }
    int cnt = 10;
    for(int d=100; d<=n; d*=10) {
        cnt++;
    }
    for(int d=1; d<=9; d++) {
        int cur = d*10+d;
        while(cur <= n) {
            cnt++; 
            cur *= 10;
            cur += d;
        }
    }
    cout << cnt;
}

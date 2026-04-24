#include <bits/stdc++.h>
using namespace std;
#define int long long
int strength(int n) {
    int ans = 1;
    while(n > 2) {
        for(int i = 2; i < n; i++) {
            if(n % i) {
                n = i;
                break;
            }
        }
        ans++;
    }
    return ans;
}
int32_t main() {
    int l, r;
    cin >> l >> r;
    int last = r - l + 1, ans = 0;
    int g = 1;
    for(int i = 2; i < 50; i++) {
        int gcd = __gcd(i, g);
        g *= (i / gcd);
        int cntl = (l - 1) / g, cntr = r / g;
        int cnt = cntr - cntl;
        ans += (last - cnt) * (strength(i) + 1);
        last = cnt;
        if(!cnt) break;
    }
    cout << ans;
}

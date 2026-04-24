#include <bits/stdc++.h>
using namespace std;
#define int long long
int solve(double R) {
    int t = R, lasth = 0, ans = 0;
    while(t) {
        double h = sqrt(R*R - t*t);
        ans += (floor(h) - lasth) * t * 2 * 2;
        lasth = floor(h);
        t--;
    }
    return ans;
} 

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int S;
    cin >> S;
    double l = 1, r = 1e6;
    while(r - l > 1e-10) {
        double m = (l+r)/2;
        if(solve(m) > S) {
            r = m;
        } else {
            l = m;
        }
    }
    cout << fixed << setprecision(10) << l;
}

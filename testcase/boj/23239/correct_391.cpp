#include <bits/stdc++.h>
using namespace std;
#define int long long
int f(int r, int i) {
    if(r <= 0) return 0;
    return (int)sqrt(r*r-i*i);
}
int32_t main() {
    int W, H, L;
    cin >> W >> H >> L;
    int ans = 0;
    for(int i=1; i<L; i++) {
        ans += 3 * f(L, i);
    }
    ans += 2 * L;
    ans += max(L - H, 0ll);
    ans += max(L - W, 0ll);
    for(int i=1; i<L; i++) {
        int lh = f(L-H, i);
        int rh = i <= W ? 0 : f(L-W, i-W);
        int ov = min(max(0ll, rh - H), lh);
        ans += lh + rh - ov;
    }
    cout << ans;
}

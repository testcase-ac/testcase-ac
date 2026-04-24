#include <bits/stdc++.h>
using namespace std;
using pii = pair<int,int>;
#define int long long

int32_t main() {
    vector<pii> pos;
    for(int a=1; a<1000; a++) {
        for(int b=1; b<1000-a; b++) {
            if(__gcd(a,b) == 1) {
                pos.push_back({a,b});
            }
        }
    }
    int A, B, C, D;
    cin >> A >> B >> C >> D;
    int ans = 0;
    for(auto f: pos) {
        int x_u = B/f.first, x_d = (A-1)/f.first + 1;
        int y_u = D/f.second, y_d = (C-1)/f.second + 1;
        int u = min(x_u, y_u), d = max(x_d, y_d);
        if(u>=d)
            ans+=(u-d+1);
    }
    cout << ans;
}

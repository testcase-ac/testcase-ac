#include <bits/stdc++.h>
using namespace std;
#define int long long

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N;
    cin >> N;
    vector<int> v(N);
    for(int i=0; i<N; i++) {
        cin >> v[i];
    }
    sort(v.begin(), v.end());
    double ans = 1;
    for(int i=0; i<N; i++) {
        double t = 1. * v[i] / (i+1);
        if(t > 1) {
            return !(cout << "impossible");
        }
        ans = min(ans, t);
    }
    cout << fixed << setprecision(8) << ans << '\n';
}

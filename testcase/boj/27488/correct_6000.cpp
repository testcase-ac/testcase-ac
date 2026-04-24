#include <bits/stdc++.h>
using namespace std;
#define int long long
#define rep(i, N) for(int i=0; i<N; i++)
#define all(x) x.begin(), x.end()

void solve() {
    int N;
    cin >> N;
    int a = 0, b = 0;
    int bias = 0, factor = 1;
    while(N) {
        int d = N%10;
    
        N /= 10;
        if(d % 2 == 0) {
            a += (d / 2) * factor;
            b += (d / 2) * factor;
        } else {
            a += (d / 2 + (bias == 0)) * factor;
            b += (d / 2 + (bias == 1)) * factor;
            bias ^= 1;
        }
        factor *= 10;
    }
    cout << a << ' ' << b << '\n';
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin >> T;
    while(T--) {
        solve();
    }
}

#include <bits/stdc++.h>
using namespace std;
#define int long long

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int a1, a0, c, n0;
    cin >> a1 >> a0 >> c >> n0;
    int fn = a1 * n0 + a0;
    if(a1 > c) {
        cout << 0;
        return 0;
    }
    cout << (fn <= c * n0);
}

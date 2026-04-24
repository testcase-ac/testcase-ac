#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 1e9+7;
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, M;
    cin >> N >> M;
    string s;
    cin >> s;
    int acc = 0;
    int ans = 1;
    for(int i=0; i<N; i++) {
        char c = s[i];
        acc *= 10;
        acc += (c - '0');
        acc %= M;
        if(!acc && i != N-1) {
            ans *= 2;
            ans %= MOD;
        }
    }
    if(!acc) {
        cout << ans;

    } else {
        cout << 0;

    }
}

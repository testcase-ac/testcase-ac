#include <bits/stdc++.h>
using namespace std;
#define int long long
int table[17][100000];
int solve() {
    int n;
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> table[0][i];
    }
    for(int l = 1; l < 17; l++) {
        int offset = 1 << (l - 1);
        for(int i = 0; i < n; i++) {
            table[l][i] = table[l - 1][i];
            if(i + offset < n) {
                table[l][i] = gcd(table[l][i], table[l - 1][i + offset]);
            }
        }
    }
    int ans = 0;
    for(int l = 0; l < n; l++) {
        int r = l, cur = table[0][l];
        while(cur && r < n) {
            cur = gcd(cur, table[0][r]);
            for(int i = 16; i >= 0; i--) {
                if(r + (1 << i) < n && gcd(cur, table[i][r]) == cur) {
                    r += (1 << i) - 1;
                }
            }
            ans = max(ans, (r - l + 1) * cur);
            r++;
        }
    }
    return ans;
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin >> T;
    while(T--)
        cout << solve() << '\n';
}

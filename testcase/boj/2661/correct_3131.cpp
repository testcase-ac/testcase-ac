#include <bits/stdc++.h>
using namespace std;
#define int long long

char ans[90];
int n;
bool solve(int cur) {
    if(cur == n) {
        cout << ans << '\n';
        return true;
    }

    for(char c = '1'; c <= '3'; c++) {
        ans[cur] = c;

        bool ok = 1;
        for(int len = 1;; len++) {
            int st1 = cur - len + 1;
            int st2 = st1 - len;
            if(st2 < 0) break;
            bool eq = 1;
            for(int i = 0; i < len; i++) {
                if(ans[st1 + i] != ans[st2 + i]) {
                    eq = 0;
                    break;
                }
            }
            if(eq) {
                ok = 0;
                break;
            }
        }
        if(ok && solve(cur + 1)) {
            return true;
        }
    }
    return false;
}
int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    solve(0);
}

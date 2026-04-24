#include <bits/stdc++.h>
using namespace std;
#define int long long

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, L;
    cin >> N >> L;
    int ans = 0, cnt = 0;
    for(int i=0; i<N; i++) {
        string s;
        cin >> s;
        int cur = 0;
        for(int j=0, k=0; j<L; j=k) {
            while(k < L && s[j] == s[k]) {
                k++;
            }
            if(s[j] == '1') {
                cur++;
            }
        }
        if(cur > ans) {
            ans = cur;
            cnt = 1;
        } else if(cur == ans) {
            cnt++;
        }
    }
    cout << ans << ' '<< cnt;
}

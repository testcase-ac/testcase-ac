#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 5e5+2;
string s;
int N;
int pre[MX], sz[MX];
int count_sz(int t) {
    int x = 0;
    while(t < N && s[t] != ' ') {
        t++;
        x++;
    }
    return x;
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    getline(cin, s);
    N = s.size();
    int cur = 0;
    sz[0] = count_sz(0);
    for(int i=0; i<N; i++) {
        if(i && isalpha(s[i]) && s[i-1] == ' ') {
            cur = i;
            pre[i-1] = cur;
            sz[i] = count_sz(i);
        }
        if(isalpha(s[i])) {
            pre[i] = cur;
        }
    }
    // 2115
    int a, b;
    cin >> a >> b;
    for(int t=a; t<=b; t++) {
        int ans = 0;
        int x = 0, line = 0;
        while(true) {
            // printf("%c%c ", s[x], s[x+1]);
            ans += sz[x];
            x += t;
            if(x >= N) break;
            line++;
            x = pre[x];
        }
        // printf("\n");
        cout << ans+line << '\n';
    }

}

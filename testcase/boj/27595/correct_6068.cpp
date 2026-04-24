#include <bits/stdc++.h>
using namespace std;
#define int long long

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N;
    cin >> N;
    string s;
    cin >> s;
    int cur = 0, mx = 0;
    for(int i=0; i<N; i++) {
        if(s[i] == 'W') {
            cur++;
        }
    }
    mx = cur;
    for(int i=N; i<2*N-1; i++) {
        if(s[i] == 'W') cur++;
        if(s[i-N] == 'W') cur--;
        mx = max(mx, cur);
    }
    cout << mx;
}

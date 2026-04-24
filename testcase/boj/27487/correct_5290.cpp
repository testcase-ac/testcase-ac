#include <bits/stdc++.h>
using namespace std;
#define int long long
#define rep(i, N) for(int i=0; i<N; i++)
#define all(x) x.begin(), x.end()
int solve() {
    int N;
    cin >> N;
    vector<int> v(N);
    int tcnt = 0;
    for(int &t: v) {
        cin >> t;
        if(t == 2) tcnt++;
    }
    for(int k=0; k<N-1; k++) {
        int p1 = 0;
        for(int i=0; i<=k; i++) {
            if(v[i] == 2) p1++;
        }
        if(p1 * 2 == tcnt) {
            return k+1;
        }
     }
     return -1;
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin >> T;
    while(T--) {
        cout << solve() << '\n';
    }
}

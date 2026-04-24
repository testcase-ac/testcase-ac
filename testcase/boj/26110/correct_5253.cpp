#include <bits/stdc++.h>
using namespace std;
#define int long long

string S;
int N;
const int MX = 1e5+3;
int dp[MX][4][4][4];
bool fn(int i, int f, int b, int k) {
    if(k < 0) return false;
    int t = N - 1 - i - b + f;
    if(!(i < t)) return true;
    int &val = dp[i][f][b][k];
    if(val != -1) return val;
    if(S[i] == S[t]) {
        val = fn(i+1, f, b, k);
    } else {
        val = max((int)fn(i+1, f+1, b, k-1), (int)fn(i, f, b+1, k-1));
    }
    // printf("dp %d %d %d %d = %d\n", i, f, b, k, val);
    return val;
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> S;
    N = S.size();
    memset(dp, -1, sizeof dp);
    for(int i=0; i<=3; i++) {
        if(fn(0, 0, 0, i)) {
            cout << i << '\n';
            return 0;
        }
    }
    cout << -1;
}

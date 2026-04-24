#include <bits/stdc++.h>
using namespace std;
#define int long long
#define rep(i, N) for(int i=0; i<N; i++)
#define all(x) x.begin(), x.end()
const int MX = 2e5+2, MOD = 998244353;
int fact[MX], factinv[MX];
int modinv(int a, int b=MOD-2) {
    int res = 1, cur = a;
    while(b) {
        if(b&1) {
            res = (res * cur) % MOD;
        }
        cur = (cur * cur) % MOD;
        b /= 2;
    }
    return res;
}
int comb(int n, int r) {
    return (((fact[n] * factinv[r]) % MOD) * factinv[n-r]) % MOD;
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    fact[0] = factinv[0] = 1;
    for(int i=1; i<MX; i++) {
        fact[i] = (fact[i-1] * i) % MOD;
        factinv[i] = modinv(fact[i]);
    }
    int N, M;
    cin >> N >> M;
    string A, B;
    cin >> A >> B;
    vector<int> b_cnts(26), a_cnts(26);
    for(char c: A) {
        a_cnts[c-'A']++;
    }
    for(char c: B) {
        b_cnts[c-'A']++;
    }
    sort(all(A));
    vector<vector<int>> dp(26);
    // 2014
    for(int c=0; c<26; c++) {
        dp[c] = vector<int>(a_cnts[c]+1);
        if(c == 0) {
            for(int i=0; i<=min(b_cnts[c], a_cnts[c]); i++) {
                dp[c][i] = 1;
                // printf("dp %lld %lld = %lld\n", c, i, dp[c][i]);
            }
            continue;
        }
        // c != 0
        int lidx = a_cnts[c-1], cur = 0; 

        for(int i=a_cnts[c]; i>=0; i--) {
            int remain = b_cnts[c] - i;
            while(remain >= 0 && lidx >= 0 && lidx >= a_cnts[c-1] - remain) {
                cur += dp[c-1][lidx] * comb(a_cnts[c-1], lidx);
                cur %= MOD;
                lidx--;
            }
            dp[c][i] = cur;
            // printf("dp %lld %lld = %lld\n", c, i, dp[c][i]);
        }
    }

    int mult = fact[N];
    for(int c=0; c<26; c++) {
        mult = (mult * factinv[a_cnts[c]]) % MOD;
    }
    // printf("mult = %lld\n", mult);
    int ans =  dp[25][a_cnts[25]];
    ans = (ans * mult) % MOD; 
    cout << ans;
}

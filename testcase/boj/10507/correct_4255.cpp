#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 1e9+9, MX = 1e6+2;
string s[3];
int p26[MX];
vector<vector<vector<int>>> dp;
vector<vector<int>> acc;
tuple<int, int, int, int> conv3dp[27*27*27];
tuple<int, int> conv2dp[27*27];
int conv3(char a, char b, char c) {
    int res = 0;
    if(a == '?') {
        res += 26;
    } else {
        res += (a  - 'a');
    }
    res *= 27;
    if(b == '?') {
        res += 26;
    } else {
        res += (b  - 'a');
    }
    res *= 27;
    if(c == '?') {
        res += 26;
    } else {
        res += (c - 'a');
    }
    return res;
}
int conv2(char a, char b) {
    int res = 0;
    if(a == '?') {
        res += 26;
    } else {
        res += (a  - 'a');
    }
    res *= 27;
    if(b == '?') {
        res += 26;
    } else {
        res += (b  - 'a');
    }
    return res;
}

// at [l, r], cricical character occured, now count from p 
int fn(int l, int r, int p) {
    int res = 1;
    for(int i=l; i<=r; i++) {
        res *= p26[acc[i][p]];
        res %= MOD;
    }
    return res;
}
// in [l, r], the order deciding character has not occurred

int dfs(int l, int r, int p) {
    if(l == r) {
        return p26[acc[l][p]];
    }
    bool all_empty = 1;
    for(int t=l; t<=r; t++) {
        if(p < s[t].size()) {
            all_empty = 0;
            break;
        }
    }
    if(all_empty) {
        return 0;
    }
    auto &res = dp[l][r][p];
    if(res != -1) {
        return res;
    }
    // printf("start dfs(%d %d %d)\n", l, r, p);
    res = 0;
    if(l+1 == r) {
        if(p >= s[l].size()) {
            return res = fn(r, r, p);
        } else if(p >= s[r].size()) {
            return res = 0ll;
        } 
        int repr = conv2(s[l][p], s[r][p]);
        auto [c1, c2] = conv2dp[repr];
        res += c1 * fn(l, r, p+1);
        res += c2 * dfs(l, r, p+1);
        res %= MOD;
        return res;
    }
    if(p >= s[0].size()) {// 0xx
        return res = dfs(1, 2, p);
    } else if(p >= s[1].size()) { // 10x
        return res = 0ll;
    } else if(p >= s[2].size()) { // 110
        return res = 0ll;
    }
    int repr = conv3(s[0][p], s[1][p], s[2][p]);
    auto [c1, c2, c3, c4] = conv3dp[repr];
    res += c1 * fn(0, 2, p+1);
    res += c2 * ((dfs(0, 1, p+1) * fn(2, 2, p+1)) % MOD);
    res %= MOD;
    res += c3 * ((dfs(1, 2, p+1) * fn(0, 0, p+1)) % MOD);
    res %= MOD;
    res += c4 * dfs(0, 2, p+1);
    res %= MOD;
    return res;
}

int solve() {
    cin >> s[0] >> s[1] >> s[2];
    const int NMX = max({s[0].size(), s[1].size(), s[2].size()}) + 42;
    dp = vector<vector<vector<int>>>(3);
    for(int i=0; i<3; i++) {
        dp[i] = vector<vector<int>>(3);
        for(int j=i+1; j<3; j++) {
            dp[i][j] = vector<int>(NMX, -1);
        }
    }
    acc = vector<vector<int>>(3, vector<int>(NMX));
    for(int i=0; i<3; i++) {
        acc[i][s[i].size()] = 0;
        for(int t=s[i].size()-1; t>=0; t--) {
            acc[i][t] = acc[i][t+1] + (s[i][t] == '?');
        }
    }
    return dfs(0, 2, 0);
}

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
    p26[0] = 1;
    for(int i=1; i<MX; i++) {
        p26[i] = (p26[i-1] * 26) % MOD;
    }
    for(int a=0; a<=26; a++) {
        for(int b=0; b<=26; b++) {
            for(int c=0; c<=26; c++) {
                int c1 = 0, c2 = 0, c3 = 0, c4 = 0;
                for(int x=0; x<26; x++) {
                    if(a != 26 && x != a) continue;
                    for(int y=x; y<26; y++) {
                        if(b != 26 && y != b) continue;
                        for(int z=y; z<26; z++) {
                            if(c != 26 && z != c) continue;
                            if(x < y && y < z) {
                                c1++;
                            } else if(x == y && y < z) {
                                c2++;
                            } else if(x < y && y == z) {
                                c3++;
                            } else {
                                c4++;
                            }
                        }
                    }
                }
                int repr = a*27*27+b*27+c;
                conv3dp[repr] = {c1, c2, c3, c4};
            }
        }
    }
    for(int a=0; a<=26; a++) {
        for(int b=0; b<=26; b++) {
            int c1 = 0, c2 = 0;
            for(int x=0; x<26; x++) {
                if(a != 26 && x != a) continue;
                for(int y=x; y<26; y++) {
                    if(b != 26 && y != b) continue;
                    if(x < y) {
                        c1++;
                    } else {
                        c2++;
                    }
                }
            }
            int repr = a*27+b;
            conv2dp[repr] = {c1, c2};
        }
    }
    int t; cin >> t;
    while (t--) cout << solve() << '\n';
}

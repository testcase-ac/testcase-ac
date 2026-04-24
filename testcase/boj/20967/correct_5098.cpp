#include <bits/stdc++.h>
using namespace std;
#define int long long

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    string s;
    cin >> s;
    map<char, int> mp;
    for(char c: s)
        mp[c] = 0;
    int chars = 0;
    for(auto &pr: mp)
        pr.second = chars++;
    vector<vector<int>> pair_count(chars, vector<int>(chars));
    for(int i = 1; i < s.size(); i++) {
        pair_count[mp[s[i - 1]]][mp[s[i]]]++;
    }
    vector<int> bitmasks;
    for(int i = 1; i < (1 << chars); i++) {
        bitmasks.push_back(i);
    }
    sort(bitmasks.begin(), bitmasks.end(), [](int a, int b) {
        return __builtin_popcount(a) < __builtin_popcount(b);
    });
    vector<int> dp(1 << chars);
    for(auto bm: bitmasks) {
        dp[bm] = 1e18;
        for(int i = 0; i < chars; i++) {
            if(bm & (1 << i)) {
                int tmp = dp[bm ^ (1 << i)];
                for(int j = 0; j < chars; j++) {
                    if(bm & (1 << j)) {
                        tmp += pair_count[i][j];
                    }
                }
                dp[bm] = min(dp[bm], tmp);
            }
        }
    }
    cout << dp[(1 << chars) - 1] + 1;
}

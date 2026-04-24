#include <bits/stdc++.h>
using namespace std;
#define int long long

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    string s;
    cin >> s;
    vector<pair<int, char>> v, stk;
    vector<pair<int, int>> ans;
    for(int i=0, j=0; i<s.size(); i=j) {
        while(j < s.size() && s[i] == s[j]) {
            j++;
        }
        v.push_back({j-i, s[i]});
    }
    stk.push_back(v[0]);
    for(int i=1; i<v.size(); i++) {
        if(v[i].second == stk.back().second) {
            stk.back().first += v[i].first;
        } else if(stk.size() == 1) {
            stk.push_back(v[i]);
        } else {
            assert(stk.size() == 2);
            int len = min(v[i].first, stk.back().first);
            int st = stk[0].first + stk[1].first - len + 1;
            int ed = st + len * 2 - 1;
            ans.push_back({st, ed});
            if(len >= stk.back().first) {
                stk.pop_back();
            } else {
                stk.back().first -= len;
            }
            if(len < v[i].first) {
                int added = v[i].first - len;
                if(v[i].second == stk.back().second) {
                    stk.back().first += added;
                } else {
                    stk.push_back({added, v[i].second});
                }
            }
        }
    }
    ans.push_back({1, stk[0].first + stk[1].first});
    cout << ans.size() << '\n';
    for(auto [a, b]: ans) {
        cout << a << ' ' << b << '\n';
    }
}

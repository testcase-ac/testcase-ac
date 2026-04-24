#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 2e5+1;
vector<int> buk[MX];
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    string s;
    cin >> s;
    int ans = 0, cnt = 0, len = 0;
    buk[0] = {-1};
    vector<int> cnt_stk = {0}, ans_stk = {0}, resets;
    for(char c: s) {
        if(c == '(') {
            cnt++;
            buk[cnt].push_back(len);
            
            cnt_stk.push_back(cnt);
            ans_stk.push_back(ans);
            len++;
        } else if(c == ')') {
            if(cnt) {
                cnt--;
                if(cnt) {
                    ans += buk[cnt].end() - lower_bound(buk[cnt].begin(), buk[cnt].end(), buk[cnt-1].back());
                } else {
                    if(resets.size())
                        ans += buk[cnt].end() - lower_bound(buk[cnt].begin(), buk[cnt].end(), resets.back());
                    else
                        ans += buk[cnt].size();
                }
            } else {
                resets.push_back(len);
            }
            buk[cnt].push_back(len);

            cnt_stk.push_back(cnt);
            ans_stk.push_back(ans);
            len++;
        } else if(c == '-') {
            buk[cnt].pop_back();
            cnt_stk.pop_back();
            ans_stk.pop_back();

            cnt = cnt_stk.back();
            ans = ans_stk.back();
            len--;
            if(resets.size() && resets.back() == len) {
                resets.pop_back();
            }
        }
        cout << ans << '\n';
    }
}

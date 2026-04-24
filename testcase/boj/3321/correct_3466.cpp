#include <bits/stdc++.h>
using namespace std;
bool arr[15001][1500];
const int THR = 1000;
short pre[15001][1500], buk[THR + 1];
struct elem {
    short v, r;
    int operator<(const elem &rhs) const {
        return v + r < rhs.v + rhs.r;
    }
};
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int R, C;
    cin >> R >> C;
    for(int i = 0; i < R; i++) {
        string s;
        cin >> s;
        for(int j = 0; j < C; j++) {
            arr[i][j] = s[j] - '0';
        }
    }
    for(int i = R - 1; i >= 0; i--) {
        for(int j = 0; j < C; j++) {
            pre[i][j] = (arr[i][j] == 0 ? 0 : pre[i + 1][j] + 1);
        }
    }
    int ans = 0;
    multiset<elem> st;
    for(short i = 0; i < R; i++) {
        memset(buk, 0, sizeof(buk));
        for(short j = 0; j < C; j++) {
            if(pre[i][j] <= THR) {
                buk[pre[i][j]]++;
            } else {
                if(!(i && pre[i - 1][j])) {
                    st.insert({pre[i][j], i});
                }
            }
        }
        while(st.size() && st.begin()->v + st.begin()->r - i <= THR) {
            st.erase(st.begin());
        }
        int cnt = 0;
        for(auto it = st.rbegin(); it != st.rend(); it++) {
            cnt++;
            auto [v, r] = *it;
            int cv = v + r - i;
            ans = max(ans, cv * cnt);
        }
        for(int j = THR; j >= 1; j--) {
            if(buk[j] == 0) continue;
            cnt += buk[j];
            ans = max(ans, cnt * j);
        }
    }
    cout << ans;
}

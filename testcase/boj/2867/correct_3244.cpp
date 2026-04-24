#include <bits/stdc++.h>
using namespace std;
#define int long long
struct elem {
    int t, c;
    int val() {
        return t * c;
    }
};

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int ans = 0, mncur = 0, mxcur = 0;
    vector<elem> mnstk, mxstk;
    for(int v: a) {
        int cnt = 1, t = v;
        while(mnstk.size() && mnstk.back().t >= v) {
            cnt += mnstk.back().c;
            t += mnstk.back().t;
            mncur -= mnstk.back().val();
            mnstk.pop_back();
        }
        mnstk.push_back({v, cnt});
        mncur += v * cnt;

        cnt = 1, t = v;
        while(mxstk.size() && mxstk.back().t <= v) {
            cnt += mxstk.back().c;
            t += mxstk.back().t;
            mxcur -= mxstk.back().val();
            mxstk.pop_back();
        }
        mxstk.push_back({v, cnt});
        mxcur += v * cnt;

        ans += mxcur - mncur;
    }
    cout << ans;
}

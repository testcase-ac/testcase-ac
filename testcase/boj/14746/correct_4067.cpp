#include <bits/stdc++.h>
using namespace std;
#define rep(i,n) for(int i=0; i<(n); i++)
#define ll long long
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
    int n, m, c1, c2, h;
    cin >> n >> m >> c1 >> c2;
    h = abs(c1-c2);
    int a[n], b[m];
    rep(i,n) cin >> a[i];
    rep(i,m) cin >> b[i];
    sort(a, a+n);
    sort(b, b+m);
    int ans = INT_MAX;
    vector<int> ansv;
    for(int t: a) {
        int lb = lower_bound(b, b+m, t) - b;
        if(lb != m) {
            int ta = abs(t-b[lb])+h;
            if(ta < ans) {
                ans = ta;
                ansv = {ta};
            } else if(ta == ans) {
                ansv.push_back(ta);
            }
        }
        if(lb - 1 >= 0) {
            int ta = abs(t-b[lb-1])+h;
            if(ta < ans) {
                ans = ta;
                ansv = {ta};
            } else if(ta == ans) {
                ansv.push_back(ta);
            }
        }
    }
    cout << ans << ' ' << ansv.size();
}

#include <bits/stdc++.h>
using namespace std;
#define int long long
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int L, N, M;
    cin >> L >> N >> M;
    vector<int> v(N);
    for(int &a: v) cin >> a;
    v.push_back(L);
    sort(v.begin(), v.end());
    int l = 0, r = L;
    while(l < r) {
        int m = (l+r+1)/2;
        int cur = 0, remove = 0;
        for(int x: v) {
            if(x - cur < m) remove++;
            else cur = x;
        }
        if(remove > M) {
            r = m-1;
        } else {
            l = m;
        }
    }
    cout << l;
}

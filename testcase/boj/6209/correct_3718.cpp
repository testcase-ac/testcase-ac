#include <bits/stdc++.h>
using namespace std;
#define int long long
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int L, N, M;
    cin >> L >> N >> M;
    vector<int> v(N);
    for(int &a: v) cin >> a;
    sort(v.begin(), v.end());
    int l = 0, r = L;
    while(l < r) {
        int m = (l+r+1)/2;
        int cur = 0, idx = 0, remain = 0;
        while(true) {
            while(idx < N && cur + m > v[idx])
                idx++;
            if(idx < N) {
                remain++;
                cur = v[idx];
                idx++;
            } else {
                break;
            }
        }
        int remove = N - remain;
        if(remove > M) {
            r = m-1;
        } else {
            l = m;
        }
    }
    cout << l;
}

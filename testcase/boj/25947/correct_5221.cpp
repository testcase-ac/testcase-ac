#include <bits/stdc++.h>
using namespace std;
#define int long long

int solve(vector<int>& v, int m, int a) {
    int ret = 0;
    int cnt = 0;
    for(int i=m-1; i>=0; i--) {
        if(cnt < a)
            ret += v[i]/2;
        else
            ret += v[i];
        cnt++;
    }
    return ret;
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(false);
    int n, b, a;
    cin >> n >> b >> a;

    vector<int> v(n);
    for(int i=0; i<n; i++) cin >> v[i];
    sort(v.begin(), v.end());
    int lo = 0, hi = n;
    while(lo != hi) {
        int mid = (lo+hi+1)/2;
        int ret = solve(v, mid, a);
        if(ret <= b) {
            lo = mid;
        }
        else {
            hi = mid-1;
        }
    }
    cout << lo;
}

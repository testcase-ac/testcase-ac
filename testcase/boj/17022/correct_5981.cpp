#include <bits/stdc++.h>
using namespace std;
#define int long long
typedef long long ll;
int bit[100001], n;
void upd(int i, int v) {
    while(i <= n) {
        bit[i] += v;
        i += i&(-i);
    }
}
int qry(int i) {
    int ret = 0;
    while(i) {
        ret += bit[i];
        i -= i&(-i);
    }
    return ret;
}

int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
    cin >> n;
    vector<int> p(n);
    for(int i=0; i<n; i++)
        cin >> p[i];
    int t = n-1;
    upd(p[n-1], 1);
    while(t && p[t-1] < p[t]) {
        t--;
        upd(p[t], 1);
    }
    cout << t << '\n';
    int st = t;
    for(int i=0; i<t; i++) {
        int q = qry(p[i]);
        cout << st+q-1 << ' ';
        st--;
        upd(p[i], 1);
    }
}

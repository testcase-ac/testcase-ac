#include <bits/stdc++.h>
using namespace std;
using ll = long long;
 
int n, m, a[300300], id[300300], ans[300300];
vector<array<int, 2>> v[300300];
 
ll t[300300];
int c[300300];

void update(int b, int val) {
    while(b <= n) t[b] += val, c[b]++, b += b & -b;
}

int find(int h) {
    int cnt = 0, b = 0;
    for(int i=19;i>=0;i--) if(b+(1<<i) <= n && h > t[b+(1<<i)]) b += 1<<i, h -= t[b], cnt += c[b];
    return b == n ? -1 : cnt+1;
}
 
int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> m;
    for(int i=1;i<=n;i++) cin >> a[i];
    for(int i=1;i<=m;i++) {
        int x, h; cin >> x >> h;
        v[x].push_back({h, i});
    }
 
    vector<array<int, 2>> p(n);
    for(int i=1;i<=n;i++) p[i-1] = {a[i], i};
    sort(p.rbegin(), p.rend());
    for(int i=0;i<n;i++) id[p[i][1]] = i+1;
 
    for(int i=1;i<=n;i++) {
        update(id[i], a[i]);
        for(auto [h, id] : v[i]) ans[id] = find(h);
    }
 
    for(int i=1;i<=m;i++) cout << ans[i] << "\n";
}
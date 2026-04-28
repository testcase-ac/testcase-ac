#include <bits/stdc++.h>
using namespace std;
int n,k,d[1000005],root;
int cnt[1000005];
vector <int> v[1000005];
void dfs(int x,int pr) {
    int ret = 0;
    for(int i : v[x]) {
        if(i == pr) continue;
        dfs(i,x);
        cnt[d[i]+1]++;
        ret = max(ret,d[i]+1);
    }
    if(pr != 0) cnt[ret]--;
    d[x] = ret;
}
void dfs2(int x,int pr) {
    d[x] = d[pr]+1;
    for(int i : v[x]) {
        if(i == pr) continue;
        dfs2(i,x);
    }
}
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> k; k = k*2-1;
    if(k == -1) {
        cout << 0;
        return 0;
    }
    int x,y;
    for(int i = 1;i < n;i++) {
        x,y; cin >> x >> y;
        v[x].push_back(y);
        v[y].push_back(x);
    }
    int po = 1;
    dfs2(1,0);
    for(int i = 2;i <= n;i++) {
        if(d[i] > d[po]) po = i;
    }
    root = po;
    memset(d,0,sizeof(d));
    dfs(root,0);
    int ans = 1;
    for(int i = n;i >= 1;i--) {
        if(k >= cnt[i]) {
            k -= cnt[i];
            ans += cnt[i]*i;
        }
        else {
            ans += k*i;
            break;
        }
    }
    cout << ans;
}

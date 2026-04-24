#include <bits/stdc++.h>
using namespace std;
const int MX = 2e5+5;
char arr[MX];
vector<int> adj[MX];
struct dpelem {
    int acnt, bcnt;
    long long adist, bdist;

    void operator+=(dpelem d) {
        acnt += d.acnt;
        bcnt += d.bcnt;
        adist += d.adist;
        bdist += d.bdist;
    }
    dpelem operator-(dpelem d) {
        dpelem res = *this;
        res.acnt -= d.acnt;
        res.bcnt -= d.bcnt;
        res.adist -= d.adist;
        res.bdist -= d.bdist;
        return res;
    }
};
dpelem down[MX], upper[MX];
int par[MX];
void dfs_down(int i, int p) {
    par[i] = p;
    if(arr[i]) {
        down[i].bcnt++;
    } else {
        down[i].acnt++;
    }
    for(int a: adj[i]) {
        if(a == p) continue;
        dfs_down(a, i);
        down[i].acnt += down[a].acnt;
        down[i].bcnt += down[a].bcnt;
        down[i].adist += down[a].adist + down[a].acnt;
        down[i].bdist += down[a].bdist + down[a].bcnt;
    }
}
void dfs_upper(int i, int p, dpelem de) {
    dpelem acc = de;
    for(int a: adj[i]) {
        if(a == p) continue;
        acc += down[a];
    }
    for(int a: adj[i]) {
        if(a == p) continue;
        dpelem cur = acc - down[a];
        cur.adist += cur.acnt;
        cur.bdist += cur.bcnt;
        if(arr[i]) {
            cur.bcnt++;
        } else {
            cur.acnt++;
        }
        upper[a] = cur;
        dfs_upper(a, i, cur);
    }
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N;
    cin >> N;
    cin >> (arr+1);
    int acnt = 0, bcnt = 0;
    for(int i=1; i<=N; i++) {
        arr[i] -= 'A';
        if(arr[i]) {
            bcnt++;
        } else {
            acnt++;
        }
    }
    if(!bcnt || !acnt) {
        return !(cout << 0);
    }
    for(int i=0; i<N-1; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs_down(1, 0);
    dfs_upper(1, 0, {0,0,0,0});
    long long ans = LLONG_MAX;
    for(int i=1; i<=N; i++) {
        int total = down[i].acnt + down[i].bcnt;
        //printf("at i = %d, total = %d\n", i, total);
        if(total == acnt) {
            long long cans = (down[i].bdist + upper[i].adist) * 2 + down[i].bcnt + upper[i].acnt;
            ans = min(ans, cans / 2);
        }

        if(total == bcnt) {
            long long cans = (down[i].adist + upper[i].bdist) * 2 + down[i].acnt + upper[i].bcnt;
            ans = min(ans, cans / 2);
        }
    }
    cout << (ans == LLONG_MAX ? -1ll : ans);
}

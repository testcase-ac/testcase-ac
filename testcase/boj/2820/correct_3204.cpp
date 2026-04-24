#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 1 << 19;
int arr[MX * 2], val[MX];
void modify(int l, int r, int v) {
    l += MX;
    r += MX;
    while(l < r) {
        if(l & 1) arr[l++] += v;
        if(r & 1) arr[--r] += v;
        l /= 2;
        r /= 2;
    }
}
int query(int p) {
    int res = 0;
    p += MX;
    while(p) {
        res += arr[p];
        p /= 2;
    }
    return res;
}

vector<int> adj[MX];
int in[MX], out[MX], idx = 1;
void dfs(int i, int p) {
    in[i] = idx++;
    for(int a: adj[i]) {
        if(a == p) continue;
        dfs(a, i);
    }
    out[i] = idx;
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, M;
    cin >> N >> M;
    for(int i = 1; i <= N; i++) {
        if(i == 1) {
            int t;
            cin >> t;
            val[i] = t;
        } else {
            int t, p;
            cin >> t >> p;
            val[i] = t;
            adj[p].push_back(i);
            adj[i].push_back(p);
        }
    }
    dfs(1, 0);

    for(int i = 0; i < M; i++) {
        string s;
        cin >> s;
        if(s[0] == 'p') {
            int a, x;
            cin >> a >> x;
            modify(in[a] + 1, out[a], x);
        } else {
            int a;
            cin >> a;
            cout << query(in[a]) + val[a] << '\n';
        }
    }
}

#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 3e5 + 1;
int arr[MX], par[MX], is_cyc[MX];
struct query {
    bool is_query;
    int x, val;
};
int f(int x) {
    return par[x] == x ? x : par[x] = f(par[x]);
}
void add_edge(int c, int p) {
    int cp = f(c), pp = f(p);
    if(cp == pp) {
        is_cyc[cp] = 1;
    } else {
        par[cp] = pp;
    }
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    int q;
    cin >> q;
    vector<query> queries(q);
    vector<int> ans;
    for(int i = 0; i < q; i++) {
        int t, x;
        cin >> t >> x;
        queries[i] = {t == 1, x, arr[x]};
        if(t == 2) {
            arr[x] = 0;
        }
    }
    reverse(queries.begin(), queries.end());
    for(int i = 1; i <= n; i++) {
        par[i] = i;
    }
    for(int i = 1; i <= n; i++) {
        if(!arr[i]) continue;
        add_edge(i, arr[i]);
    }
    for(auto &q: queries) {
        if(q.is_query) {
            int p = f(q.x);
            if(is_cyc[p]) {
                ans.push_back(-1);
            } else {
                ans.push_back(p);
            }
        } else {
            add_edge(q.x, q.val);
        }
    }
    reverse(ans.begin(), ans.end());
    for(auto &a: ans) {
        if(a == -1)
            cout << "CIKLUS\n";
        else
            cout << a << '\n';
    }
}

#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MXN = 2005, MXM = 2e5 + 2;
int N, M;
struct FenwickTree2D {
    vector<vector<int>> bit;
    int n, m;

    FenwickTree2D(int n, int m): n(n), m(m) {
        bit.assign(n, vector<int>(m, LLONG_MIN));
    }

    int mx(int x, int y) {
        int ret = LLONG_MIN;
        for (int i = x; i < n; i = i | (i + 1))
            for (int j = y; j < m; j = j | (j + 1)) {
                // printf("bit[%lld][%lld] = %lld\n", i, j, bit[i][j]);
                ret = max(ret, bit[i][j]);
            }
        return ret;
    }

    void add(int x, int y, int val) {
        for (int i = x; i >= 0; i = (i & (i + 1)) - 1)
            for (int j = y; j >= 0; j = (j & (j + 1)) - 1) 
                bit[i][j] = val;
    }
};
struct info {
    int l, r, v, i;
};
int ans[MXM];
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> N >> M;
    vector<int> arr(N+1);
    FenwickTree2D ft(N+1, N+1);
    for(int i=1; i<=N; i++) cin >> arr[i];
    vector<info> updates;
    for(int i=1; i<=N; i++) {
        int sm = 0;
        for(int j=i; j<=N; j++) {
            sm += arr[j];
            updates.push_back({i, j, sm, 0});
        }
    }
    sort(updates.begin(), updates.end(), [](info a, info b) {
        return a.v < b.v;
    });
    vector<info> queries(M);
    for(int i=0; i<M; i++) {
        cin >> queries[i].l >> queries[i].r >> queries[i].v;
        queries[i].i = i;
    }
    sort(queries.begin(), queries.end(), [](info a, info b) {
        return a.v < b.v;
    });
    int k = 0;
    for(int i=0, j=0; i<updates.size(); i=j) {

        while(k < queries.size() && queries[k].v < updates[i].v) {
            // printf("queries[%lld] = %lld\n", k, queries[k].v);
            int l = queries[k].l, r = queries[k].r;
            int mx = ft.mx(l, N + 1 - r);
            ans[queries[k].i] = mx;
            k++;
        }
        while(j < updates.size() && updates[i].v == updates[j].v) {
            // printf("updates: j = %lld, v = %lld, l = %lld, r = %lld\n", j, updates[j].v, updates[j].l, updates[j].r);
            ft.add(updates[j].l, N + 1 - updates[j].r, updates[j].v);
            j++;
        }
    }
    while(k < queries.size()) {
        // printf("queries[%lld] = %lld\n", k, queries[k].v);
        int l = queries[k].l, r = queries[k].r;
        int mx = ft.mx(l, N + 1 - r);
        ans[queries[k].i] = mx;
        k++;
    }
    for(int i=0; i<M; i++) {
        if(ans[i] == LLONG_MIN) cout << "NONE\n";
        else cout << ans[i] << '\n';
    }
}

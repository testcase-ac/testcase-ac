#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
typedef tree<int,null_type,less_equal<int>,rb_tree_tag,tree_order_statistics_node_update> set_t;
set_t X;
struct fish {
    int x, y;
};
int ans[200001];
// 2007
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, M, L;
    cin >> N >> M >> L;
    vector<fish> v(N);
    set_t st;
    for(auto &a: v) {
        cin >> a.x >> a.y;
        st.insert(a.x + a.y);
    }
    sort(v.begin(), v.end(), [](fish a, fish b) {
        return (a.x - a.y) < (b.x - b.y);
    });
    vector<pair<int, int>> queries(M);
    for(auto &pr: queries) {
        cin >> pr.first;
    }
    for(int i=0; i<M; i++) {
        queries[i].second = i;
    }
    sort(queries.begin(), queries.end());
    int cur = 0;
    for(auto [q, idx]: queries) {
        // printf("at q = %d\n", q);
        while(cur < v.size() && v[cur].x - v[cur].y < (q-L)) {
            int to_find = v[cur].x + v[cur].y;
            // printf("  erase %d\n", to_find);
            st.erase(st.find_by_order(st.order_of_key(to_find)));
            cur++;
        }
        // printf(" current st = ");
        // for(auto t: st) {
        //     // printf("%d ", t);
        // }
        // printf("\n");
        ans[idx] = st.order_of_key(q+L+1);
        // printf("  query for x+y = %d, found ans %d\n", q+L+1,ans[idx]);

    }
    for(int i=0; i<M; i++) {
        cout << ans[i] << '\n';
    }
}

#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

using namespace std;
#define int long long
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> set_t;
int N;

int solve(vector<int> a, vector<int> b) {
    map<int, int> mp_a;
    for(int i = 0; i < N; i++) {
        mp_a[a[i]] = i;
    }
    map<int, int> mp;
    for(int i = 0; i < N; i++) {
        mp[b[i]] = i;
    }
    vector<int> perm;
    for(int i = 0; i < N; i++) {
        perm.push_back(mp[a[i]]);
    }
    int cur = 0;
    set_t s;
    for(int i = 0; i < N; i++) {
        s.insert(perm[i]);
        cur += i - s.order_of_key(perm[i]);
    }
    vector<pair<int, int>> prs;
    for(int i = 0; i < N; i++) {
        prs.push_back({perm[i], i});
    }
    int ans = cur;
    sort(prs.begin(), prs.end());
    for(auto [num, pos]: prs) {
        cur -= pos;
        cur += N - 1 - pos;
        ans = min(ans, cur);
    }
    return ans;
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> N;
    vector<int> a(N), b(N);
    for(int i = 0; i < N; i++) {
        cin >> a[i];
    }
    for(int i = 0; i < N; i++) {
        cin >> b[i];
    }
    cout << min(solve(a, b), solve(b, a));
}

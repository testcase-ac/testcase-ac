#include <bits/stdc++.h>
using namespace std;
int arr[1000001];
int ans[1000001];
int cnt[1000001];
const int BUK = 1024;
struct Query {
    int l, r, i;
};
int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int N;
    cin >> N;
    for(int i = 1; i <= N; i++) {
        cin >> arr[i];
    }
    // arr를 좌표압축
    vector<int> tmp(arr + 1, arr + N + 1);
    sort(tmp.begin(), tmp.end());
    unique(tmp.begin(), tmp.end());
    for(int i = 1; i <= N; i++) {
        arr[i] = lower_bound(tmp.begin(), tmp.end(), arr[i]) - tmp.begin();
    }

    int Q;
    cin >> Q;
    vector<Query> queries(Q);
    int idx = 0;
    for(auto &q: queries) {
        cin >> q.l >> q.r;
        q.i = idx;
        idx++;
    }
    sort(queries.begin(), queries.end(), [](const Query &a, const Query &b) {
        if(a.l / BUK != b.l / BUK) {
            return a.l / BUK < b.l / BUK;
        }
        return ((a.l / BUK) & 1) ? a.r < b.r : a.r > b.r;
    });
    int cur_ans = 0;
    int cl = 0, cr = 0;
    auto add_at = [&cur_ans](int i) {
        if(!cnt[arr[i]])
            cur_ans++;
        cnt[arr[i]]++;
    };
    auto remove_at = [&cur_ans](int i) {
        if(!i)
            return;
        cnt[arr[i]]--;
        if(!cnt[arr[i]])
            cur_ans--;
    };
    for(auto &q: queries) {
        while(cr < q.r) {
            cr++;
            add_at(cr);
        }
        while(cl > q.l) {
            cl--;
            add_at(cl);
        }
        while(cr > q.r) {
            remove_at(cr);
            cr--;
        }
        while(cl < q.l) {
            remove_at(cl);
            cl++;
        }
        ans[q.i] = cur_ans;
    }
    for(int i = 0; i < Q; i++) {
        cout << ans[i] << '\n';
    }
}

#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 5e5+5;
int ans[MX], A[MX], seg[MX*2], N;

int query(int l, int r) {
    l += N, r += N;
    int res = LLONG_MAX;
    while(l < r) {
        if(l&1) res = min(res, seg[l++]);
        if(r&1) res = min(res, seg[--r]);
        l /= 2, r /= 2;
    }
    return res;
}
int find_first_index(int l, int r, int t) {
    while(l < r) {
        int m = (l+r)/2;
        if(query(l, m+1) < t) {
            r = m;
        } else {
            l = m+1;
        }
    }
    return r;
}
int find_last_index(int l, int r, int t) {
    while(l < r) {
        int m = (l+r+1)/2;
        if(query(m, r+1) < t) {
            l = m;
        } else {
            r = m-1;
        }
    }
    return l;
}
struct cand {
    int l, r, h;
    bool operator<(cand c) {return h < c.h;}
};
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> N;
    for(int i=0; i<N; i++) {
        cin >> A[i];
        seg[i+N] = A[i];
    }
    for(int i=N-1; i>=0; i--) {
        seg[i] = min(seg[i*2], seg[i*2+1]);
    }
    vector<cand> cands;
    vector<vector<cand>> in(N), out(N);
    priority_queue<int> pq, del_pq;
    for(int i=0; i<N; i++) {
        int lft_ext = find_last_index(0, i, A[i]), rht_ext = find_first_index(i+1, N-1, A[i]);
        if(A[lft_ext] < A[i]) {
            lft_ext++;
        }
        if(A[rht_ext] < A[i]) {
            rht_ext--;
        }
        cand c = {lft_ext, rht_ext, A[i]};
        in[lft_ext].push_back(c);
        out[rht_ext].push_back(c);
        pq.push((rht_ext-lft_ext+1) * A[i]);
    }
    for(int i=0; i<N; i++) {
        // i번을 제거!
        for(auto [l, r, h]: in[i]) {
            del_pq.push((r-l+1)*h);
            pq.push((r-l)*h);
        }
        while(pq.size() && del_pq.size() && pq.top() == del_pq.top()) {
            pq.pop();
            del_pq.pop();
        }
        ans[i] = pq.top();

        for(auto [l, r, h]: out[i]) {
            del_pq.push((r-l)*h);
            pq.push((r-l+1)*h);
        }
    }

    for(int i=0; i<N; i++) {
        sort(in[i].begin(), in[i].end());
        sort(out[i].begin(), out[i].end());
    }
    for(int i=1; i<N-1; i++) {
        for(auto [l, r, h]: out[i-1]) {
            auto it = lower_bound(in[i+1].begin(), in[i+1].end(), (cand){0,0,h});
            if(it != in[i+1].end()) {
                ans[i] = max(ans[i], (it->r - l)*h);
            }
        }
        for(auto [l, r, h]: in[i+1]) {
            auto it = lower_bound(out[i-1].begin(), out[i-1].end(),(cand){0,0,h});
            if(it != out[i-1].end()) {
                ans[i] = max(ans[i], (r - it->l) *h);
            }
        }
    }

    for(int i=0; i<N; i++) {
        cout << ans[i] << ' ';
    }
}

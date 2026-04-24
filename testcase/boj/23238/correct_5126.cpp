#include <bits/stdc++.h>
using namespace std;
const int BUK = 100;
const int MX = 1e5 + BUK * 2;
int prep[MX / BUK][MX / BUK];
struct qry {
    int l, r;
};
vector<int> V;
void compress(vector<int> &A) {
    V = A;
    sort(V.begin(), V.end());
    V.erase(unique(V.begin(), V.end()), V.end());
    for(int &a: A)
        a = lower_bound(V.begin(), V.end(), a) - V.begin();
}
vector<int> buk[MX];
int buk_cnt(int t, int l, int r) {
    auto it_l = lower_bound(buk[t].begin(), buk[t].end(), l);
    auto it_r = upper_bound(buk[t].begin(), buk[t].end(), r);
    return it_r - it_l;
}
int cnt[MX];
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, Q;
    cin >> N >> Q;
    vector<int> A(N+1);
    for(int i=1; i<=N; i++) {
        cin >> A[i];
    }
    compress(A);
    for(int i=1; i<=N; i++) {
        buk[A[i]].push_back(i);
    }
    vector<qry> queries(Q);

    for(int i=0; i<=N; i+=BUK) {
        memset(cnt, 0, sizeof cnt);
        int repr = 0, mx_cnt = 0;
        for(int j=i; j<=N; j++) {
            cnt[A[j]]++;
            if(cnt[A[j]] > mx_cnt) {
                mx_cnt = cnt[A[j]];
                repr = A[j];
            } else if(cnt[A[j]] == mx_cnt && A[j] > repr) {
                repr = A[j];
            }
            if(j % BUK == (BUK - 1)) {
                prep[i / BUK][j / BUK] = repr;
            }
        }
    }

    for(auto &[l, r]: queries) {
        cin >> l >> r;
        int lb = l / BUK, rb = r / BUK;
        int ans = 0, anscnt = 0;
        for(int t=l;t / BUK == l / BUK && t <= N;t++) {
            int cnt = buk_cnt(A[t], l, r);
            if(cnt > anscnt || (cnt == anscnt && ans < A[t])) {
                ans = A[t];
                anscnt = cnt;
            }
        }

        for(int t=r; t / BUK == r / BUK && t >= 1; t--) {
            int cnt = buk_cnt(A[t], l, r);
            if(cnt > anscnt || (cnt == anscnt && ans < A[t])) {
                ans = A[t];
                anscnt = cnt;
            } 
        }
        int cnt = buk_cnt(prep[lb+1][rb-1], l, r);
        if(cnt > anscnt || (cnt == anscnt && ans < prep[lb+1][rb-1])) {
            ans = prep[lb+1][rb-1];
            anscnt = cnt;
        }
        cout << V[ans] << '\n';
    }
}

#include <bits/stdc++.h>

using namespace std;
#define int long long
#define rep(i, N) for(int i=0; i<N; i++)
struct info {
    int w, d;
    bool operator<(const info &i) const {
        return w < i.w;
    }
};
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, M;
    cin >> N >> M;
    vector<int> A(N), B(N);
    rep(i, N) cin >> A[i];
    rep(i, N) cin >> B[i];
    int ans = 0;
    for(int ld=0; ld<N; ld++) {
        for(int rd=0; rd<N; rd++) {
            vector<int> v;
            if(N - ld <= rd) {
                continue;
            }
            // printf("ld = %lld, rd = %lld\n", ld, rd);
            int move_cnt = min(ld, rd) * 2 + max(ld, rd);
            if(move_cnt >= M) continue;
            int play_cnt = M - move_cnt;
            priority_queue<info> pq;
            for(int i=N-ld; i<N; i++) {
                pq.push({A[i], B[i]});
            }
            for(int i=0; i<=rd; i++) {
                pq.push({A[i], B[i]});
            }
            int cur_ans = 0;
            for(int i=0; i<play_cnt; i++) {
                auto [w, d] = pq.top();
                pq.pop();
                cur_ans += w;
                pq.push({max(w-d, 0ll), d});
            }
            // printf("play_cnt = %d, cur_ans = %d\n", play_cnt, cur_ans);
            ans = max(ans, cur_ans);
        }
    }
    cout << ans;
}

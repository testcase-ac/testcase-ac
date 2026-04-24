#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#define ll long long
#define eps 1e-7
#define all(x) ((x).begin()),((x).end())
#define usecppio ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
using namespace std;
#define int ll
using pii = pair<int, int>;
struct rect {
    int rl, rh, wl, wh;
    void read() {
        cin >> rl >> rh >> wl >> wh;
    }
};
const int MX = 101010, SQRT = 520;
int buk_offset[SQRT], buk_cnt[SQRT][MX], base_num[MX], buk_over_k[SQRT], K;
void update_ind(int t, int diff) {
    int bk = t / SQRT;
    buk_cnt[bk][base_num[t]]--;
    if(diff == 1) {
        base_num[t]++;
        buk_cnt[bk][base_num[t]]++;
        if(base_num[t] + buk_offset[bk] == K) {
            buk_over_k[bk]++;
        }
    } else if(diff == -1) {
        base_num[t]--;
        buk_cnt[bk][base_num[t]]++;
        if(base_num[t] + buk_offset[bk] == K - 1) {
            buk_over_k[bk]--;
        }
    }
}
void update(int l, int r, int diff) {
    int l_bk = l / SQRT, r_bk = r / SQRT;
    for(int i=l; i<=r && i<(l_bk+1)*SQRT; i++) {
        update_ind(i, diff);
    }
    if(l_bk != r_bk) {
        for(int i=r_bk*SQRT; i<=r; i++) {
            update_ind(i, diff);
        }
    }
    for(int bk=l_bk+1; bk<r_bk; bk++) {
        if(diff == 1) {
            buk_offset[bk]++;
            buk_over_k[bk] += buk_cnt[bk][K - buk_offset[bk]];
        } else {
            buk_over_k[bk] -= buk_cnt[bk][K - buk_offset[bk]];
            buk_offset[bk]--;
        }
    }
}

int query(int l, int r) {
    int l_bk = l / SQRT, r_bk = r / SQRT;
    int ans = 0;
    for(int i=l; i<=r && i<(l_bk+1)*SQRT; i++) {
        assert(i / SQRT == l_bk);
        ans += (base_num[i] + buk_offset[l_bk]) >= K;
    }
    if(l_bk != r_bk) {
        for(int i=r_bk*SQRT; i<=r; i++) {
            assert(i / SQRT == r_bk);
            ans += (base_num[i] + buk_offset[r_bk]) >= K;
        }
    }

    for(int bk=l_bk+1; bk<r_bk; bk++) {
        ans += buk_over_k[bk];
    }
    return ans;
}

int32_t main()
{
    usecppio;
    int N, H, W, D;
    cin >> N >> K >> H >> W >> D;
    vector<rect> rects(N);
    vector<vector<rect>> starts(MX), ends(MX);
    for(int i=0; i<N; i++) {
        rects[i].read();
        starts[rects[i].rl].push_back(rects[i]);
        ends[rects[i].rh].push_back(rects[i]);
    }
    buk_cnt[0][0] = SQRT-1;
    for(int bk=1; bk<SQRT; bk++) {
        buk_cnt[bk][0] = SQRT;
    }
    int ans = 0;
    for(int r=1; r<=MX; r++) {
        for(auto rec: starts[r]) {
            update(rec.wl, rec.wh, 1);
        }

        if(H-D <= r && r <= H+D) {
            // printf("query at r = %lld\n", r);
            int q = query(max(W-D, 1ll), min(W+D, MX));
            // printf("result is %lld\n", q);
            ans += q;
        }

        for(auto rec: ends[r]) {
            update(rec.wl, rec.wh, -1);
        }
    }
    cout << ans;
}

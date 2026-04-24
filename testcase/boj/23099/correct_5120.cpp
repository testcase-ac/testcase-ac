#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(0);cin.tie(0);
    int H, T;
    cin >> H >> T;
    vector<int> C(H);
    for(int &t: C) {
        cin >> t;
        if(t > 16) {
            return !(cout << 0);
        }
    }
    vector<pair<int,int>> teams(T);
    for(auto &[d, i]: teams) {
        cin >> d >> i;
    }
    vector<int> blocks;
    for(int h=1; h<=16; h++) {
        for(int i=0, j=0; i<H; i=j) {
            while(j < H && (C[i] >= h) == (C[j] >= h)) {
                j++;
            }
            if(C[i] < h) continue;
            int dst = j - i;
            blocks.push_back(dst);
        }
    }
    if(blocks.size() > 16 || blocks.size() == 0) {
        // printf("no ans\n");
        return !(cout << 0);
    }
    map<int, vector<int>> bm_bucket;
    for(int bm=0; bm<(1<<T); bm++) {
        int len = 0;
        for(int i=0; i<T; i++) {
            if((bm & (1 << i))) {
                len += teams[i].first;
            }
        }
        // printf("len = %d, bm = %d\n", len, bm);
        bm_bucket[len].push_back(bm);
    }
    vector<vector<int>> dp(blocks.size(), vector<int>(1<<T));
    int block_len_acc = 0;
    for(int b=0; b<blocks.size(); b++) {
        int cur_block = blocks[b];
        block_len_acc += cur_block;
        // printf("at b = %d, cur = %d, acc = %d\n", b, cur_block, block_len_acc);
        for(int bm: bm_bucket[block_len_acc]) {
            // printf("  at block_len_acc = %d, bm = %d\n", block_len_acc, bm);
            for(int bm2: bm_bucket[cur_block]) {
                // check submask
                if(((bm & bm2) != bm2)) continue;
                int prv_bm = bm ^ bm2;
                if((!b && !prv_bm) || (b && dp[b-1][prv_bm])) {
                    // printf("  ok at cur bm = %d, prv bm = %d\n", bm, prv_bm);
                    dp[b][bm] = 1;
                    break;
                }
            }
        }
    }
    // printf("last\n");
    int ans = 0;
    for(int bm=1; bm<(1<<T); bm++) {
        if(dp[blocks.size()-1][bm]) {
            int cur = 0;
            for(int i=0; i<T; i++) {
                if(bm & (1 << i)) {
                    cur += teams[i].second;
                }
            }
            ans = max(ans, cur);
        }
    }
    cout << ans;
}

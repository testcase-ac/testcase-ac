#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int N, K;
void rotate(vector<int> &v) {
    int ed = v.back();
    for(int i=2*N-1; i>0; i--) {
        v[i] = v[i-1];
    }
    v[0] = ed;
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> N >> K;
    vector<int> cnt(N*2), robot(N*2);
    for(int i=0; i<2*N; i++)
        cin >> cnt[i];

    int zero_cnt = 0;
    for(int t=1;;t++) {
        rotate(cnt);
        rotate(robot);
        if(robot[N-1]) {
            robot[N-1] = 0;
        }
        vector<pair<int, int>> locs;
        for(int i=0; i<2*N; i++) {
            if(robot[i]) {
                locs.push_back({robot[i], i});
            }
        }
        sort(locs.begin(), locs.end());
        for(auto [rt, ri]: locs) {
            int next_i = (ri == 2*N-1 ? 0 : ri+1);
            if(!robot[next_i] && cnt[next_i]) {
                cnt[next_i]--;
                swap(robot[next_i], robot[ri]);
                if(!cnt[next_i])
                    zero_cnt++;
            }
            if(robot[N-1]) {
                robot[N-1] = 0;
            }
        }
        if(!robot[0] && cnt[0]) {
            cnt[0]--;
            robot[0] = t;
            if(!cnt[0]) {
                zero_cnt++;
            }
        }
        if(zero_cnt >= K) {
            return !(cout << t);
        }
    }
}

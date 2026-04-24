#include <bits/stdc++.h>
using namespace std;
#define int long long
using pii = pair<int,int>;

int dp[100020];
int psum[100020];
priority_queue<pii, vector<pii>, greater<pii>> pq;
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N;
    cin >> N;
    vector<int> values(N);
    for(int i=0; i<N; i++) cin >> values[i];
    pq.push({0, -1});
    psum[0] = 0;
    for(int i=0; i<N; i++) {
        psum[i+1] = psum[i] + values[i];
        int max_idx = -1;
        pii max_val;
        while(!pq.empty()) {
            auto top = pq.top();
            if(top.first <= psum[i+1]) {
                pq.pop();
                if(top.second > max_idx) {
                    max_idx = top.second;
                    max_val = top;
                }
            }
            else
                break;
        }
        // cout << "i: " << max_idx << endl;
        if(max_idx != -1) {
            dp[i] = psum[i+1] - psum[max_idx+1];
            pq.push(max_val);
        }
        else {
            dp[i] = psum[i+1];
        }
        pq.push({dp[i]+psum[i+1], i});
    }

    // for(int i=0; i<N; i++) {
    //     cout << dp[i] << " ";
    // }
    // cout << "\n";
    int ans = dp[N-1];
    for(int i=N-1; i>0; i--) {
        if(psum[N]-psum[i] < dp[i-1]) {
            ans = min(ans, dp[i-1]);
        }
    }
    cout << ans;
}

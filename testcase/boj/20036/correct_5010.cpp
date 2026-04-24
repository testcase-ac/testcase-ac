#include <bits/stdc++.h>
using namespace std;

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N;
    cin >> N;
    vector<int> arr(N), cp;
    for(int i=0; i<N; i++) {
        cin >> arr[i];
    }
    cp = arr;
    sort(cp.begin(), cp.end());
    cp.erase(unique(cp.begin(), cp.end()), cp.end());
    for(auto &a: arr) {
        a = lower_bound(cp.begin(), cp.end(), a) - cp.begin();
    }
    vector<vector<int>> buk(N);
    for(int i=0; i<N; i++) {
        buk[arr[i]].push_back(i);
    }
    int ans = INT_MAX;
    for(int i=0; i<cp.size(); i++) {
        ans = min(ans, N - (int)buk[i].size());
        if(i + 1 == cp.size())
            continue;
        for(int j=0; j<buk[i].size(); j++) {
            int cnt = buk[i+1].end() - lower_bound(buk[i+1].begin(), buk[i+1].end(), buk[i][j]);
            ans = min(ans, N - (cnt + j+1));
        }
    }
    for(int i=0, j=0; i<cp.size(); i=j) {
        int tmp = 0;
        while(j < cp.size() && (i == j || buk[j].front() > buk[j-1].back())) {
            tmp += buk[j].size();
            j++;
        }
        if(i) {
            tmp += lower_bound(buk[i-1].begin(), buk[i-1].end(), buk[i].front()) - buk[i-1].begin();
        }
        if(j < cp.size()) {
            tmp += buk[j].end() - lower_bound(buk[j].begin(), buk[j].end(), buk[j-1].back());
        }
        ans = min(ans, N - tmp);
    }
    cout << ans;
}

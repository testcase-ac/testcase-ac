#include <bits/stdc++.h>
using namespace std;

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N;
    cin >> N;
    vector<pair<int, int>> A(N);
    int cur = 0;
    for(auto &[a, b]: A) {
        cin >> a >> b;
    }
    priority_queue<int, vector<int>, greater<int>> pq;
    sort(A.begin(), A.end());
    int ans = 0;
    for(auto &[start, end]: A) {
        while(pq.size() && pq.top() <= start) {
            pq.pop();
        }
        pq.push(end);
        ans = max(ans, (int)pq.size());
    }
    
    vector<int> use_counts(ans);
    set<int> indexes;
    set<pair<int, int>> end_times; // {time, index}
    for(int i=0; i<ans; i++) {
        indexes.insert(i);
    }
    for(auto &[start, end]: A) {
        while(end_times.size() && end_times.begin()->first <= start) {
            indexes.insert(end_times.begin()->second);
            end_times.erase(end_times.begin());
        }
        int idx = *indexes.begin();
        indexes.erase(indexes.begin());
        end_times.insert({end, idx});
        use_counts[idx]++;
    }
    cout << ans << '\n';
    for(int i=0; i<ans; i++) {
        cout << use_counts[i] << ' ';
    }
}

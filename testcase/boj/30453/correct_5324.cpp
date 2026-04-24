#include <bits/stdc++.h>
using namespace std;
const int MX = 3005;
pair<int, int> arr[MX];
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N;
    cin >> N;
    for(int i=0; i<N; i++) {
        cin >> arr[i].first >> arr[i].second;
    }
    vector<pair<int, int>> v;
    int ans = 0;
    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            int x = arr[i].first + arr[j].first;
            int y = arr[i].second + arr[j].second;
            v.push_back({x, y});
        }
    }
    sort(v.begin(), v.end());
    for(int i=0, j=0; i<v.size(); i=j) {
        while(j<v.size()&&v[i] == v[j]) j++;
        ans = max(ans, j-i);
    }
    cout << ans;
}

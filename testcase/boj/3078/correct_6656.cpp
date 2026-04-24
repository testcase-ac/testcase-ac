#include <iostream>
#include <map>
#include <vector>

#define int long long
using namespace std;
int32_t main() {
    ios::sync_with_stdio(0);cin.tie(0);
    int N, K;
    cin >> N >> K;
    vector<int> arr(N);
    map<int, int> mp;
    int ans = 0;
    for(int i=0; i<N; i++) {
        string s;
        cin >> s;
        arr[i] = s.size();
        ans += mp[s.size()];
        mp[arr[i]]++;
        if(i >= K) {
            mp[arr[i-K]]--;
        }
    }
    cout << ans;
}

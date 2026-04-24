#include <bits/stdc++.h>
using namespace std;
#define int long long

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int K, N;
    cin >> K >> N;
    vector<int> tmp(K);
    vector<string> v(K);
    for(int i = 0; i < K; i++) {
        cin >> tmp[i];
        v[i] = to_string(tmp[i]);
    }
    int mx_elem = *max_element(tmp.begin(), tmp.end());
    for(int i = 0; i < N - K; i++) {
        v.push_back(to_string(mx_elem));
    }
    string ans = "";
    sort(v.begin(), v.end(), [](const string &a, const string &b) {
        return (a + b) > (b + a);
    });
    for(int i = 0; i < v.size(); i++) {
        ans += v[i];
    }
    cout << ans << '\n';
}

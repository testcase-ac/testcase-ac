#include "bits/stdc++.h"
using namespace std;

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    vector<int> good;
    good.push_back(202021);
    good.push_back(20202021);
    for(int i = 0; i <= 9; i++){
        good.push_back(202002021 + i * 10000);
    }
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<int> v(n);
        for(int i = 0; i < n; i++){
            cin >> v[i];
        }
        sort(v.begin(), v.end());
        long long ans = 0;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < good.size(); j++){
                auto t = equal_range(v.begin() + i, v.end(), good[j] - v[i]);
                ans += (t.second - t.first);
            }
        }
        cout << ans << '\n';
    }
}

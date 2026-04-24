#include <bits/stdc++.h>
using namespace std;
#define int long long

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N;
    cin >> N;
    string s;
    cin >> s;
    map<char,int> mp;
    for(int i=0; i<N/2; i++) {
        mp[s[i]]++;
    }
    for(int i=(N+1)/2; i<N; i++) {
        mp[s[i]]++;
    }
    for(auto pr: mp) {
        if(pr.second % 2 ==1) {
            return !(cout << "No\n");
        }
    }
    cout << "Yes\n";
}

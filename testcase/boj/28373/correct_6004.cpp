#include <bits/stdc++.h>
using namespace std;
#define int long long

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    string s;
    cin >> s;
    vector<int> v;
    for(int i=0; i<s.size()-1; i++) {
        if(s[i] == 'S' && s[i+1] == 'S') {
            v.push_back(i);
        }
    }
    for(char c: s) {
        cout << (char)(c - 'A' + 'a');
    }
    cout << '\n';
    for(int t: v) {
        for(int i=0; i<s.size(); i++) {
            if(t == i) {
                cout << 'B';
                i++;
            } else {
                cout << (char)(s[i] - 'A' + 'a');
            }
        }
        cout << '\n';
    }

}

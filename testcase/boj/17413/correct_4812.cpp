#include <bits/stdc++.h>
using namespace std;
#define int long long

int32_t main() {
    string s;
    getline(cin, s);
    string ans;
    for(int i = 0, j = 0; i < s.size(); i = j) {
        if(s[i] == '<') {
            while(j < s.size() && s[j] != '>') {
                j++;
            }
            j++;
            ans += s.substr(i, j - i);
        } else {
            while(j < s.size() && s[j] != ' ' && s[j] != '<') {
                j++;
            }
            auto t = s.substr(i, j - i);
            reverse(t.begin(), t.end());
            ans += t;
            if(s[j] == ' ') {
                ans += ' ';
                j++;
            }
        }
    }
    cout << ans;
}

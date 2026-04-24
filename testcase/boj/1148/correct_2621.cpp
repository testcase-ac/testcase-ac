#include <bits/stdc++.h>
using namespace std;
#define int long long

int cnt[26], ptn[26];
string uniqueize(string &s) {
    string ret;
    sort(s.begin(), s.end());
    for(int i = 0; i < s.size(); i++) {
        if(i == 0 || s[i] != s[i - 1]) {
            ret += s[i];
        }
    }
    return ret;
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    vector<string> v;

    vector<string> query;
    while(true) {
        string s;
        cin >> s;
        if(s == "-") break;
        sort(s.begin(), s.end());
        v.push_back(s);
    }
    while(true) {
        string pattern;
        cin >> pattern;
        if(pattern == "#") break;
        memset(cnt, 0, sizeof(cnt));

        for(string &w: v) {
            memset(ptn, 0, sizeof(ptn));
            for(char c: pattern) {
                ptn[c - 'A']++;
            }
            bool ok = 1;
            for(char c: w) {
                if(--ptn[c - 'A'] < 0) {
                    ok = 0;
                    break;
                }
            }
            if(ok) {
                for(int i = 0, j = 0; i < w.size(); i = j) {
                    while(j < w.size() && w[i] == w[j]) j++;
                    cnt[w[i] - 'A']++;
                }
            }
        }
        int mn = INT_MAX, mx = 0;
        pattern = uniqueize(pattern);
        for(char c: pattern) {
            // printf("cnt of %c is %d\n", c, cnt[c - 'A']);
            mn = min(mn, cnt[c - 'A']);
            mx = max(mx, cnt[c - 'A']);
        }
        for(char c: pattern) {
            if(cnt[c - 'A'] == mn) {
                cout << c;
            }
        }
        cout << ' ' << mn << ' ';
        for(char c: pattern) {
            if(cnt[c - 'A'] == mx) {
                cout << c;
            }
        }
        cout << ' ' << mx << '\n';
        // printf("-----\n");
    }
}

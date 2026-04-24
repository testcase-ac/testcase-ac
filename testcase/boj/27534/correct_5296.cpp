#include <bits/stdc++.h>
using namespace std;
#define int long long
/*
000
001
010
011
100

0100
*/
int brute(string s) {
    int ans = 1000;
    for(int bm=0; bm<(1<<s.size()); bm++) {
        int cnt = __popcount(bm);
        bool ok = 1;
        for(int i=0; i<s.size(); i++) {
            if(bm & (1<<i)) {
                if(s[i] == '0') s[i] = '1';
                else s[i] = '0';
            }
        }

        vector<int> v;
        for(int i=0, j=0; i<s.size(); i=j) {
            while(j < s.size() && s[i] == s[j]) j++;
            v.push_back(j-i);
        }
        ok = (v.size() % 2 == 0 && v[0] == v.back());
        if(ok) {
            ans = min(ans, cnt);
        }

        for(int i=0; i<s.size(); i++) {
            if(bm & (1<<i)) {
                if(s[i] == '0') s[i] = '1';
                else s[i] = '0';
            }
        }
    }
    return ans == 1000 ? -1 : ans;
}
int solve(string s) {
    int ans = INT_MAX;
    
    int fcost = s[0] != '1', bcost = s[s.size()-1] != '0';
    for(int t=1; t<=(s.size() / 2 - 1); t++) {
        if(s[t] == '0') {
            fcost++;
        }
        if(s[t-1] == '0') {
            fcost--;
        } else {
            fcost++;
        }

        if(s[s.size()-1-t] == '1') {
            bcost++;
        }
        if(s[s.size()-t] == '1') {
            bcost--;
        } else {
            bcost++;
        }
        //printf("at t = %lld, added = %lld\n", t, fcost+bcost);
        ans = min(ans, fcost + bcost);
    }

    if(s.size() % 2 == 0) {
        int cnt = 0;
        for(int i=0; i<s.size() /2; i++) {
            cnt += s[i] == '0';
        }
        for(int i=s.size()/2; i<s.size(); i++) {
            cnt += s[i] == '1';
        }
        ans = min(ans, cnt);
    }
    return ans;
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin >> T;
    while(T--) {
        int n;
        string s;
        cin >> n >> s;
        int ans = 0;
        if(n == 1 || n == 3) {
            ans = -1;
        } else {
            int a = solve(s);
            for(int i=0; i<n; i++) {
                if(s[i] == '0') {
                    s[i] = '1';
                } else {
                    s[i] = '0';
                }
            }
            int b = solve(s);
            
            ans = min(a, b);

        }
        // int brt = brute(s);
        // if(brt != ans)
        //     printf("brt = %lld, ans = %lld\n", brt, ans);
        cout << ans << '\n';
    }
}

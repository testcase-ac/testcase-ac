#include <bits/stdc++.h>
#define rep(i,n) for(int i=0; i<(n); i++)
#define sz(x) ((int)(x).size())
#define ll long long
using namespace std;
string s;
int main() {
    cin >> s;
    vector<char> v;
    for(char c: s) {
        if(c != 'A' && c != 'P') return !(cout <<"NP");
        v.push_back(c);
        if(sz(v) >= 4) {
            int n = sz(v);
            if(v[n-4] == 'P' && v[n-3] == 'P' && v[n-2] == 'A' && v[n-1] == 'P')
                rep(i,3) v.pop_back();
        }
    }
    if(sz(v) == 1 && v[0] == 'P')
        cout << "PPAP";
    else cout <<"NP";

}

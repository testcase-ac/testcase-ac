#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

string Xor(string s, string t){
    if(t.size() < s.size()) t = string(s.size()-t.size(), '0') + t;
    for(int i=0; i<s.size(); i++) s[i] = s[i] != t[i] ? '1' : '0';
    if(int p=s.find('1'); p == -1) return "0";
    else return s.substr(p);
}

string Solve(int n, string s){
    if(count(s.begin(), s.end(), '1') == 0) return "0";
    if(count(s.begin(), s.end(), '0') == 0) return s.back() = '0', s;
    int pos = s.find('1'), len = 0;
    while(pos+len < n && s[pos+len] == '1') len++;
    if(pos + len == n) return s.substr(pos);
    pos += len;
    for(int i=1; i<=len && pos+i<s.size(); i++) if(s[pos+i] == '1') return Xor(s, s.substr(pos-i, n-pos));
    return Xor(s, s.substr(pos-len, n-pos));
}

int main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int TC; cin >> TC;
    for(int tc=1; tc<=TC; tc++){
        int N; string S; cin >> N >> S;
        cout << Solve(N, S) << "\n";
    }
}
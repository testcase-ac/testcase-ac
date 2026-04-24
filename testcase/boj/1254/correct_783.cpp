#include <bits/stdc++.h>
#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i,n) for(int i=0; i<(n); i++)
#define pii pair<int,int>
#define deb(v) cout << #v << ':' << v << '\n';

using namespace std;
string s;
bool ispali(int i) {
	for(int j=sz(s)-1;;i++, j--) {
		if(j <= i) return true;
		if(s[i] != s[j]) return false;
	}
}
int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	cin >> s;
	for(int i=0;;i++) {
		if(ispali(i)) return !(cout << sz(s)+i);
	}
}

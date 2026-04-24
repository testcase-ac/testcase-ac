#include <bits/stdc++.h>
#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i,n) for(int i=0; i<(n); i++)
#define pii pair<int,int>
#define deb(v) cout << #v << ':' << v << '\n';

using namespace std;

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	string s;
	cin >> s;
	int i=0, n=sz(s);
	while(i < n) {
		if(i+1<n && s[i] == 'p' && s[i+1] == 'i') i+=2;
		else if(i+1<n && s[i]=='k' && s[i+1]=='a') i+=2;
		else if(i+2<n && s[i]=='c' && s[i+1] == 'h' && s[i+2] == 'u') i+=3;
		else return !(cout << "NO");
	}
	cout << "YES";
}

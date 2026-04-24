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
	int a, b, c;
	cin >> a >> b >> c;
	if(b >= c) cout << -1;
	else {
		//a+b*ans <= c*ans -> ans = a/(c-b)
		cout << (a/(c-b)+1);
	}
}

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
	int n;
	cin >> n;
	int a[n];
	rep(i,n) cin >> a[i];
	int g = __gcd(a[0], a[1]);
	if(n == 3) g = __gcd(a[2],g);
	for(int i=1; i<=g/2; i++)
		if(g%i == 0) cout << i << '\n';
	cout << g;
}

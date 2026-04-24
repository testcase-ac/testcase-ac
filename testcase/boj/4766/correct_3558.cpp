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
	string a, b;
	cin >> a;
	while(1) {
		cin >> b;
		if(b == "999") break;
		double x = stod(a), y = stod(b);
		cout << fixed << setprecision(2) << (y-x) << '\n';
		a = b;
	}
}

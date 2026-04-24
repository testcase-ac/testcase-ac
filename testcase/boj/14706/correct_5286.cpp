#include <bits/stdc++.h>
using namespace std;

#define ll long long
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, m;
	cin >> n >> m;
	vector<ll> upbnd(n+1, 1e18L);
	upbnd[0] = 0;
	for(int i=0; i<m; i++) {
		int l, s;
		cin >> l >> s;
		for(int j=1; j<=n; j++) {
			upbnd[j] = min(upbnd[j], ((j-1)/l+1)*(ll)s);
			if(j-l>0)
				upbnd[j] = min({upbnd[j], upbnd[j-l]+s, upbnd[j-l]+s});
		}
	}
	for(int i=1; i<=n; i++) {
		cout << upbnd[i] << '\n';
	}
}

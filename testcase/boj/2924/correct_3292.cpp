#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MX = 5e5+2;
int shuf[MX];
bool seen[MX];
ll cdiv(ll a, ll b) {return (a+b-1)/b;}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, c, d;
	ll a, b;
	cin >> n >> a >> b >> c >> d;
	for(int i=1; i<=n; i++) {
		cin >> shuf[i];
	}
	ll period = 1;
	for(int i=c+1; i<=n-d; i++) {
		if(seen[i]) continue;
		int cur = i;
		ll sz = 0;
		while(!seen[cur]) {
			seen[cur] = 1;
			sz++;
			cur = shuf[cur];
		}
		ll g = __gcd(period, sz);
		period = period / g * sz;
		if(period >= 2e12) break;
	}
	cout << cdiv(b-1, period) - cdiv(a-1, period);
}

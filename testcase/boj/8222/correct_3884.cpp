#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 1e6+2;
int sieve[MX], dist[MX], a[100000], ans[100000], ansv[100000];
vector<int> buk[MX];
void chk(int x, int y) {
	int g = gcd(a[x], a[y]), v = dist[a[x]] + dist[a[y]] - 2* dist[g];
	if(v < ansv[x] || (v == ansv[x] && y < ans[x])) {
		ansv[x] = v;
		ans[x] = y;
	}
	if(v < ansv[y] || (v == ansv[y] && x < ans[y])) {
		ansv[y] = v;
		ans[y] = x;
	}
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	memset(ansv, 0x3f, sizeof ansv);
	for(int i=2; i*i<MX; i++) {
		if(sieve[i]) continue;
		for(int j=i*i; j<MX; j+=i) {
			sieve[j] = i;
		}
	}
	dist[1] = 0;
	for(int i=2; i<MX; i++) {
		if(!sieve[i])
			dist[i] = 1;
		else
			dist[i] = dist[i/sieve[i]] + 1;
	}
	int n;
	cin >> n;
	for(int i=0; i<n; i++) {
		cin >> a[i];
		for(int j=1; j*j<=a[i]; j++) {
			if(a[i] % j == 0) {
				buk[j].push_back(i);
				if(j*j != a[i]) {
					buk[a[i]/j].push_back(i);
				}
			}
		}
	}
	for(int i=1; i<MX; i++) {
		if(buk[i].empty()) continue;
		auto it = min_element(buk[i].begin(), buk[i].end(), [&](int x, int y){return dist[a[x]] < dist[a[y]];});
		swap(*it, buk[i][0]);
		for(int j=1; j<buk[i].size(); j++) {
			chk(buk[i][0], buk[i][j]);
		}
	}
	for(int i=0; i<n; i++) {
		cout << ans[i]+1 << '\n';
	}
}

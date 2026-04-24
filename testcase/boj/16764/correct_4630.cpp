#include <bits/stdc++.h>
using namespace std;
const int MX = 5e4;
vector<int> flav[MX];
int mp[1000001];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	for(int i=0; i<n; i++) {
		for(int j=0; j<5; j++) {
			int t;
			cin >> t;
			flav[i].push_back(t);
			mp[t] = 1;
		}
	}
	int ptr = 0;
	for(int i=0; i<=1000000; i++) {
		if(mp[i])
			mp[i] = ptr++;
	}
	vector<bitset<MX>> bits(ptr);
	for(int i=0; i<n; i++) {
		for(int j=0; j<5; j++) {
			bits[mp[flav[i][j]]][i] = 1;
		}
	}
	long long ans = 0;
	for(int i=0; i<n; i++) {
		bitset<MX> cur = bits[mp[flav[i][0]]];
		for(int j=1; j<5; j++)
			cur |= bits[mp[flav[i][j]]];
		ans += n - cur.count();
	}
	cout << ans / 2;
}

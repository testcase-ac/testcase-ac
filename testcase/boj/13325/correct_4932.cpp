#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	n++;
	int edge[1<<n] = {}, node[1<<n] = {};
	long long ans = 0;
	for(int i=2; i<(1<<n); i++) {
		cin >> edge[i];
	}
	for(int i=(1<<(n-1))-1;i>=1;i--) {
		int l = i<<1, r = l|1;
		int mx = max(edge[l]+node[l], edge[r]+node[r]);
		ans += mx*2-node[l]-node[r];
		node[i] = mx;
	}
	cout << ans;
}

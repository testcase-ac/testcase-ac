#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9+7;
int a[100000], p[100001];
int f(int l, int r) {
	int two = 0, neg = 0, pos = 0;
	for(int i=l; i<r; i++) {
		if(abs(a[i]) == 2)
			two++;
		if(a[i] < 0)
			neg++;
		else
			pos++;
	}
	if(neg % 2 == 0)
		return two;
	if(!pos && neg == 1)
		return -1;
	int tmp = 0, mn = 1e9;
	for(int i=l; i<r; i++) {
		if(abs(a[i]) == 2)
			tmp++;
		if(a[i] < 0)
			break;
	}
	mn = tmp;
	tmp = 0;
	for(int i=r-1; i>=l; i--) {
		if(abs(a[i]) == 2)
			tmp++;
		if(a[i] < 0)
			break;
	}
	mn = min(mn, tmp);
	return two - mn;
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	p[0] = 1;
	for(int i=1; i<=100000; i++) {
		p[i] = p[i-1]*2;
		p[i] %= MOD;
	}
	int T;
	cin >> T;
	while(T--) {
		int n;
		cin >> n;
		for(int i=0; i<n; i++) {
			cin >> a[i];
		}
		int j = 0, ans = -1;
		for(int i=0; i<n; i=j) {
			if(a[i] == 0) {
				j++;
				continue;
			}
			while(j < n && a[j] != 0)
				j++;
			ans = max(ans, f(i, j));
		}
		cout << (ans == -1 ? 0 : p[ans]) << '\n';
	}
}

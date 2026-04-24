#include <bits/stdc++.h>
using namespace std;

int a[15000];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, m;
	cin >> n >> m;
	for(int i=0; i<n; i++) {
		cin >> a[i];
	}
	sort(a, a+n);
	int l = 0, r = n-1, ans = 0;
	while(l < r) {
		if(a[l]+a[r] == m) {
			ans++;
			l++;
			r--;
		} else if(a[l]+a[r] < m) {
			l++;
		} else {
			r--;
		}
	}
	cout << ans;
}

#include <bits/stdc++.h>
using namespace std;
#define ll long long
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, m;
	cin >> n >> m;
	int a[m];
	for(int i=0; i<m; i++) {
		cin >> a[i];
	}
	int l = 1, r = 1e9;
	while(l < r) {
		int mid = (l+r)/2;
		ll cnt = 0;
		for(int i=0; i<m; i++)
			cnt += (a[i]+mid-1) / mid;
		if(cnt > n)
			l = mid+1;
		else
			r = mid;
	}
	cout << l;
}

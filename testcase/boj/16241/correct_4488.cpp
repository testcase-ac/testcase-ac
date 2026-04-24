#include <bits/stdc++.h>
using namespace std;
int a[100000], b[100000];
/*
1 2 6 7 10
3 6 9 11 12
*/
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, m;
	cin >> n >> m;
	for(int i=0; i<n; i++) {
		cin >> a[i];
	}
	for(int i=0; i<m; i++) {
		cin >> b[i];
	}
	sort(a, a+n);
	sort(b, b+m);
	int *small, *large;
	if(n <= m) {
		small = a;
		large = b;
	} else {
		small = b;
		large = a;
		swap(n,m);
	}
	int l = 0, r = 1e9+1, mid;
	while(l < r) {
		mid = (l+r)/2;
		int j = 0;
		bool ok = true;
		for(int i=0; i<n; i++) {
			while(j<m && abs(large[j]-small[i]) > mid)
				j++;
			if(j == m) {
				ok = false;
				break;
			}
			j++;
		}
		if(ok)
			r = mid;
		else
			l = mid+1;
	}
	cout << l;
}

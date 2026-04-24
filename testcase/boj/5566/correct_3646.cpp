#include <bits/stdc++.h>
using namespace std;
const int MX = 1e3+1;
int arr[MX];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, m;
	cin >> n >> m;
	for(int i=1; i<=n; i++) {
		cin >> arr[i];
	}
	int p = 1;
	for(int t=1; t<=m; t++) {
		int r;
		cin >> r;
		p += r;
		if(p >= n)
			return !(cout << t);
		if(p >= 1)
			p += arr[p];
		if(p >= n)
			return !(cout << t);
	}
}

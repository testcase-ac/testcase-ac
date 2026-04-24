#include <bits/stdc++.h>
using namespace std;
int arr[1001];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int L, n;
	cin >> L >> n;
	int a = 0, av = 0, b = 0, bv = 0;
	for(int i=1; i<=n; i++) {
		int l, r;
		cin >> l >> r;
		if(r-l+1 > av) {
			av = r-l+1;
			a = i;
		}
		int cnt = 0;
		for(int j=l; j<=r; j++) {
			if(!arr[j]) cnt++;
			arr[j] = 1;
		}
		if(cnt > bv) {
			bv = cnt;
			b = i;
		}
	}
	printf("%d\n%d", a, b);
}

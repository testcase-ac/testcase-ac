#include <bits/stdc++.h>
using namespace std;
/*
(2l+t-1)*t/2 = n
2lt+t^2-t = 2n
l = (2n+t-t^2)/2t

*/
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int ans = 0, n;
	cin >> n;
	for(int t=1;; t++) {
		int a = 2*n+t-t*t, b = 2*t;
		if(a / b < 1) break;
		if(a % b == 0) ans++;
	}
	cout << ans;
}

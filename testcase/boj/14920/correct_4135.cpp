#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	long long n;
	cin >> n;
	int ans = 1;
	while(n != 1) {
		if(n&1) n = 3*n+1;
		else n /= 2;
		ans++;
	}
	cout << ans;
}

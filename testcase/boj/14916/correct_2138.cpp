#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, ans = INT_MAX;
	cin >> n;
	for(int i=0;n-i*5>=0; i++) {
		if((n-i*5) % 2 == 0) {
			ans = min(ans, i+(n-i*5)/2);
		}
	}
	cout << (ans == INT_MAX ? -1 : ans);
}

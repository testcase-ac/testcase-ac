#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	int ans = 0;
	for(int i=1; i<n; i++) {
		for(int j=i+2; n-i-j>0; j++) {
			if((n-i-j)%2==0) ans++;
		}
	}
	cout << ans;
}

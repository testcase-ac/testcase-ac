#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, ans = 0;
	cin >> n;
	for(int i=1; i<=300; i++) {
		for(int j=i; j<=300; j++) {
			if(j*j-i*i == n) ans++;
		}
	}
	cout << ans;
}

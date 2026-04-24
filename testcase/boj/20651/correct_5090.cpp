#include <bits/stdc++.h>
using namespace std;
#define int long long

int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	vector<int> v(n);
	for(int i=0; i<n; i++) {
		cin >> v[i];
	}
	int ans = 0;
	for(int i=0; i<n; i++) {
		for(int j=i; j<n; j++) {
			int s = 0;
			for(int k=i; k<=j; k++) {
				s += v[k];
			}
			if(s % (j-i+1) == 0) {
				int t = s / (j-i+1);
				for(int k=i; k<=j; k++) {
					if(v[k] == t) {
						ans++;
						break;
					}
				}
			}
		}
	}
	cout << ans;
}

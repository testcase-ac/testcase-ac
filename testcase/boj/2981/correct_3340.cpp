#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	int a[n];
	for(int i=0; i<n; i++)
		cin >> a[i];
	sort(a, a+n);
	int g = a[1] - a[0];
	for(int i=2; i<n; i++)
		g = __gcd(g, a[i]-a[i-1]);
	vector<int> ans = {g};
	for(int i=2;i*i<=g; i++) {
		if(g%i==0) {
			ans.push_back(i);
			if(i*i!=g)
				ans.push_back(g/i);
		}
	}
	sort(ans.begin(), ans.end());
	for(int t: ans) cout << t << ' ';
}

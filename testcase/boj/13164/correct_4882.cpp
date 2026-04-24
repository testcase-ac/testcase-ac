#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, k;
	cin >> n >> k;
	vector<int> a(n);
	vector<ll> diff(n-1);
	for(int i=0; i<n; i++) {
		cin >> a[i];
		if(i)
			diff[i-1] = a[i] - a[i-1];
	}
	sort(diff.begin(), diff.end(), greater<ll>());
	ll tot = accumulate(diff.begin(), diff.end(), 0ll);
	for(int i=0; i<k-1; i++) {
		tot -= diff[i];
	}
	cout << tot;
}

#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 1e6+2;
int a[MX];
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	for(int i=0; i<n; i++) {
		cin >> a[i];
	}
	priority_queue<int> pq;
	pq.push(a[0]);
	int ans = 0;
	for(int i=1; i<n; i++) {
		a[i] -= i;
		if(a[i] < pq.top()) {
			ans += pq.top()-a[i];
			pq.push(a[i]);
			pq.push(a[i]);
			pq.pop();
		} else {
			pq.push(a[i]);
		}
	}
	cout << ans;
}

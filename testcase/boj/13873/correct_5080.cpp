#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 1e5+2;
int a[MX];
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, k;
	cin >> n >> k;
	for(int i=0; i<n; i++)
		cin >> a[i];
	int sum = accumulate(a, a+n, 0ll);
	priority_queue<int> pq;
	for(int i=n-1; i>=0; i--) {
		pq.push(a[i]);
		if((i-k) % (k+1) == 0) {
			sum -= pq.top();
			pq.pop();
		}
	}
	cout << sum;
}

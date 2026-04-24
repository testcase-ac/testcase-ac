#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MXL = 3e14, MX = 3e5;
int arr[MX], acc[MX], n, k;
// 0 3 11 8 10 15 17
bool solve(int T) { // k개보다 많거나 같은가?
	priority_queue<int, vector<int>, greater<int>> pq;
	int cnt = 0;
	vector<int> tmp;
	pq.push(0);
	for(int i=1; i<=n; i++) {
		tmp.clear();
		while(pq.size() && acc[i] - pq.top() >= T) {
			tmp.push_back(pq.top());
			pq.pop();
			cnt++;
			if(cnt >= k)
				return 1;
		}
		for(int t: tmp)
			pq.push(t);
		pq.push(acc[i]);
	}
	return 0;
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> n >> k;
	for(int i=1; i<=n; i++) {
		cin >> arr[i];
		acc[i] = acc[i-1] + arr[i];
	}
	int l = 0, r = MXL * 2;
	while(l < r) {
		int m = (l+r+1)/2;
		if(solve(m-MXL)) {
			l = m;
		} else {
			r = m-1;
		}
	}
	l -= MXL;
	vector<int> v, tmp;
	priority_queue<int, vector<int>, greater<int>> pq;
	pq.push(0);
	for(int i=1; i<=n; i++) {
		tmp.clear();
		while(pq.size() && acc[i] - pq.top() >= l+1) {
			tmp.push_back(pq.top());
			v.push_back(acc[i] - pq.top());
			pq.pop();
		}
		for(int t: tmp)
			pq.push(t);
		pq.push(acc[i]);
	}
	while(v.size() < k) {
		v.push_back(l);
	}
	sort(v.begin(), v.end(), greater<int>());
	for(int t: v)
		cout << t << ' ';
}

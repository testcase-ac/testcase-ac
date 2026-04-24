#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, k;
	cin >> n >> k;
	pair<int, int> items[n];
	for(int i=0; i<n; i++) {
		cin >> items[i].first >> items[i].second;
	}
	sort(items, items+n);
	int bags[k];
	for(int i=0; i<k; i++)
		cin >> bags[i];
	sort(bags, bags+k);
	priority_queue<int> pq;
	long long ans = 0;
	int i = 0;
	for(int b: bags) {
		while(i < n && items[i].first <= b) {
			int p = items[i++].second;
			pq.push(p);
		}
		if(!pq.empty()) {
			ans += pq.top();
			pq.pop();
		}
	}
	cout << ans;
}
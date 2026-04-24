#include <bits/stdc++.h>
using namespace std;
vector<int> buk[1001];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	for(int i=0; i<n; i++) {
		int d, w;
		cin >> d >> w;
		buk[d].push_back(w);
	}
	priority_queue<int, vector<int>, greater<int>> pq;
	for(int i=1; i<=1000; i++) {
		sort(buk[i].begin(), buk[i].end(), greater<int>());
		for(int t: buk[i]) {
			if(pq.size() < i)
				pq.push(t);
			else if(t > pq.top()) {
				pq.pop();
				pq.push(t);
			} else {
				break;
			}
		}
	}
	int ans = 0;
	while(pq.size()) {
		ans += pq.top();
		pq.pop();
	}
	cout << ans;
}

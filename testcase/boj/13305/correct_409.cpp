#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	n--;
	int dist[n], cost[n];
	for(int i=0; i<n; i++) {
		cin >> dist[i];
	}
	for(int i=0; i<n; i++) {
		cin >> cost[i];
	}
	int curr = 1e9+7;
	long long ans = 0;
	for(int i=0; i<n; i++) {
		curr = min(curr, cost[i]);
		ans += (long long)curr*dist[i];
	}
	cout << ans;
}
#include <bits/stdc++.h>
using namespace std;

const int MX = 20;
int dist[MX][MX];
bool rm[MX][MX];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			cin >> dist[i][j];
		}
	}
	for(int k=0; k<n; k++) {
		for(int i=0; i<n; i++) {
			for(int j=0; j<n; j++) {
				if(i == j || i == k || j == k) continue;
				if(dist[i][k] + dist[k][j] == dist[i][j])
					rm[i][j] = true;
				else if(dist[i][k] + dist[k][j] < dist[i][j])
					return !(cout << -1);
			}
		}
	}
	int ans = 0;
	for(int i=0; i<n; i++) {
		for(int j=i+1; j<n; j++) {
			if(rm[i][j] || i == j) continue;
			ans += dist[i][j];
		}
	}
	cout << ans;
}

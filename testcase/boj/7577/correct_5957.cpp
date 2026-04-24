#include <bits/stdc++.h>
using namespace std;
struct edge {
	int u, v, w;
};
vector<edge> arr;
int dist[41];
bool relax() {
	bool ok = 0;
	for(edge e: arr) {
		if(dist[e.v] > dist[e.u]+e.w) {
			dist[e.v] = dist[e.u]+e.w;
			ok = 1;
		}
	}
	return ok;
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	memset(dist, 0x3f, sizeof dist);
	dist[0] = 0;
	int k, n;
	cin >> k >> n;
	for(int i=0; i<k; i++) {
		arr.push_back({i, i+1, 1});
		arr.push_back({i+1, i, 0});
	}
	for(int i=0; i<n; i++) {
		int x, y, r;
		cin >> x >> y >> r;
		arr.push_back({y, x-1, -r});
		arr.push_back({x-1, y, r});
	}
	for(int t=0; t<k; t++) {
		relax();
	}
	if(relax())
		return !(cout << "NONE");
	for(int i=1; i<=k; i++) {
		if(dist[i] != dist[i-1])
			cout << '#';
		else
			cout << '-';
	}
}

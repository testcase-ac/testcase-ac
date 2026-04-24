#include <bits/stdc++.h>
#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i,n) for(int i=0; i<(n); i++)
#define pii pair<int,int>
#define deb(v) cout << #v << ':' << v << '\n';

using namespace std;
struct comp {
	bool operator() (const pii &a, const pii &b) const{
		return a.first > b.first;
	}
};
int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int n;
	cin >> n;
	int buildt[n], depcnt[n] = {}, ans[n];
	vector<vector<int>> adj(n);
	rep(i,n) {
		cin >> buildt[i];
		int t;
		cin >> t;
		while(t != -1) {
			adj[t-1].push_back(i);
			depcnt[i]++;
			cin >> t;
		}
	}
	priority_queue<pii, vector<pii>, comp> pq;
	rep(i,n) {
		if(!depcnt[i])
			pq.emplace(buildt[i], i);
	}
	int ftime;
	while(!pq.empty()) {
		auto pr = pq.top();
		pq.pop();
		ftime = pr.first;
		int i = pr.second;
		ans[i] = ftime;
		for(int a: adj[i]) {
			depcnt[a]--;
			if(!depcnt[a])
				pq.emplace(ftime+buildt[a], a);
		}
	}
	for(int a: ans) cout << a << '\n';
}

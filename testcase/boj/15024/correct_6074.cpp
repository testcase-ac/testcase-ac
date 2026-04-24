#include <bits/stdc++.h>
using namespace std;
#define int long long
map<string,int> mp;
string invmap[500];
vector<int> adj[500];
int dist[500], prv[500];
int chk(int t) {
	memset(dist, 0x3f, sizeof dist);
	memset(prv, -1, sizeof prv);
	queue<pair<int, int>> que({{t, 0}});
	while(que.size()) {
		int q, d;
		tie(q, d) = que.front();
		que.pop();
		for(int a: adj[q]) {
			if(dist[a] > d+1) {
				dist[a] = d+1;
				prv[a] = q;
				que.push({a, dist[a]});
			}
		}
	}
	return dist[t];
}
int32_t main() {
	int n;
	cin >> n;
	for(int i=0; i<n; i++) {
		string &s = invmap[i];
		cin >> s;
		mp[s] = i;
	}
	for(int i=0; i<n; i++) {
		string s;
		int t;
		cin >> s >> t;
		//printf("s = %s | t = %d\n", s.c_str(), t);
		cin.get();
		while(t--) {
			getline(cin, s);
			//printf("getline = %s\n", s.c_str());
			istringstream iss(s);
			iss >> s;
			while(!iss.eof()) {
				iss >> s;
				if(s.back() == ',')
					s.pop_back();
				//printf("go to %s\n", s.c_str());
				int num = mp[s];
				adj[i].push_back(num);
			}
		}
	}
	int ans = INT_MAX;
	vector<int> ansv;
	for(int i=0; i<n; i++) {
		int t = chk(i);
		if(ans > t) {
			ans = t;
			int cur = i;
			ansv.clear();
			do {
				ansv.push_back(cur);
				cur = prv[cur];
			} while(cur != i);
		}
	}
	if(ans == INT_MAX)
		cout << "SHIP IT";
	else {
		reverse(ansv.begin(), ansv.end());
		for(int t: ansv)
			cout << invmap[t] << ' ';
	}

}

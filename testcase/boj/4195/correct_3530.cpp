#include <bits/stdc++.h>
#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i,n) for(int i=0; i<(n); i++)
#define pii pair<int,int>
#define deb(v) cout << #v << ':' << v << '\n';

using namespace std;

#define MAXN 200000
int parent[MAXN], setsz[MAXN];
int find(int i){return parent[i] == i ? i : parent[i] = find(parent[i]);}
void joinroot(int i, int j) {
	if(i != j) {
		parent[i] = j;
		setsz[j] += setsz[i];
	}
}
int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int T;
	cin >> T;
	while(T--) {
		int i = 0, f;
		cin >> f;
		map<string, int> mp;
		while(f--) {
			string a, b;
			int ia, ib;
			cin >> a >> b;
			if(mp.find(a) == mp.end()) {
				mp[a] = i;
				parent[i] = i;
				setsz[i] = 1;
				ia = i++;
			} else {
				ia = find(mp.find(a)->second);
			}
			if(mp.find(b) == mp.end()) {
				mp[b] = i;
				parent[i] = i;
				setsz[i] = 1;
				ib = i++;
			} else {
				ib = find(mp.find(b)->second);
			}
			joinroot(ia, ib);
			cout << setsz[ib] << '\n';
		}
	}
}

#include <bits/stdc++.h>
using namespace std;
const int MX = 50007;
string arr[MX*2], invindex[MX*2];
vector<int> adj[MX*2];
bool seen[MX*2];
int dfs(int i) {
	seen[i] = true;
	int repr = 0;
	if(isdigit(invindex[i][0]))
		repr = stoi(invindex[i]);
	for(int a: adj[i]) {
		if(!seen[a]) {
			int r = dfs(a);
			if(repr) {
				if(r && r != repr) {
					cout << "NE";
					exit(0);
				}
			} else {
				if(r)
					repr = r;
			}
		} 
	}
	return repr;
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	map<string,int> index;
	int t = 0;
	for(int i=0; i<2*n; i++) {
		cin >> arr[i];
		if(!index.count(arr[i])) {
			index[arr[i]] = t;
			invindex[t++] = arr[i];
		}
	}
	for(int i=0; i<n; i++) {
		int a = index[arr[i]], b = index[arr[n+i]];
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	for(int i=0; i<t; i++) {
		if(!seen[i])
			dfs(i);
	}
	cout << "DA";
}

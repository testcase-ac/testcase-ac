#include <bits/stdc++.h>
using namespace std;

pair<int, int> tree[10001];
int col[10001];
bool ischild[10001];
int colnow = 0;
vector<pair<int, int>> record;
void dfs(int i, int l) {
	if((int)record.size() < l) record.emplace_back(INT_MAX, INT_MIN);
	if(tree[i].first != -1) dfs(tree[i].first, l+1);
	col[i] = ++colnow;
	record[l-1].first = min(record[l-1].first, colnow);
	record[l-1].second = max(record[l-1].second, colnow);
	if(tree[i].second != -1) dfs(tree[i].second, l+1);
}

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int n;
	cin >> n;
	while(n--) {
		int t, l, r;
		cin >> t >> l >> r;
		tree[t].first = l;
		tree[t].second = r;
		if(l != -1) ischild[l] = true;
		if(r != -1) ischild[r] = true;
	}
	int p=1;
	for(;;p++)
		if(!ischild[p]) break;
	dfs(p, 1);
	int mlev = 1, width = 1;
	for(int i=0; i<(int)record.size(); i++) {
		if(record[i].second - record[i].first + 1 > width) {
			width = record[i].second - record[i].first + 1;
			mlev = i+1;
		}
	}
	cout << mlev << ' ' << width;
}

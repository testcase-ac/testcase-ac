#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	map<int, int> mp;
	int k, l;
	cin >> k >> l;
	for(int i=0; i<l; i++) {
		int p;
		cin >> p;
		mp[p] = i;
	}
	vector<pair<int, int>> v(mp.begin(), mp.end());
	sort(v.begin(), v.end(), [](pair<int, int> &a, pair<int, int> &b){return a.second < b.second;});
	for(int i=0; i<min(k, (int)v.size()); i++)
		printf("%08d\n", v[i].first);
}

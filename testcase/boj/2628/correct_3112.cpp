#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int r, c, k;
	cin >> c >> r >> k;
	vector<int> row, col;
	while(k--) {
		int t, v;
		cin >> t >> v;
		if(t)
			col.push_back(v);
		else
			row.push_back(v);
	}
	sort(col.begin(), col.end());
	sort(row.begin(), row.end());
	col.push_back(c);
	row.push_back(r);
	adjacent_difference(col.begin(), col.end(), col.begin());
	adjacent_difference(row.begin(), row.end(), row.begin());
	cout << (*max_element(col.begin(), col.end()) * (*max_element(row.begin(), row.end())));
}

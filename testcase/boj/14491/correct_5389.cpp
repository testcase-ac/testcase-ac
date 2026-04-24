#include <bits/stdc++.h>
using namespace std;
vector<int> ans;
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int t;
	cin >> t;
	while(t) {
		ans.push_back(t%9);
		t /= 9;
	}
	reverse(ans.begin(), ans.end());
	for(int a: ans) cout << a;
}

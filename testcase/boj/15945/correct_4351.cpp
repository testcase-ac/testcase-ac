#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	vector<int> v;
	bool pos = false, neg = false;
	for(int i=0; i<n; i++) {
		int t;
		cin >> t;
		if(t)
			v.push_back(t);
		if(t > 0) pos = true;
		else if (t < 0) neg = true;
	}
	if(!pos && !neg) cout << 0;
	else if(pos && neg) {
		cout << 0;
	} else {
		sort(v.begin(), v.end());
		if(pos) {
			cout << min(v.front(), v.back()-v.front());
		} else {
			cout << min(-v.back(), v.back()-v.front());
		}
	}
}

#include <bits/stdc++.h>
using namespace std;
#define int long long

int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	vector<int> sq, v;
	for(int i=1; i*i<=INT_MAX; i++) {
		sq.push_back(i*i);
	}
	for(int i=1; i*i<=INT_MAX; i++) {
		int t = (i+1)*i/2;
		if(binary_search(sq.begin(), sq.end(), t+1)) {
			v.push_back(t+1);
			//printf("pushed %d\n", v.back());
		}
	}
	int a, b, i = 0;
	while(++i) {
		cin >> a >> b;
		if(!a)
			return 0;
		cout << "Case " << i << ": ";
		cout << lower_bound(v.begin(), v.end(), b) - lower_bound(v.begin(), v.end(), a+1) << '\n';
	}
}

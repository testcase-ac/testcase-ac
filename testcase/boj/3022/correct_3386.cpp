#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	map<string,int> mp;
	int n, ans = 0;
	cin >> n;
	for(int i=0; i<n; i++) {
		string s;
		cin >> s;
		if(mp[s] > (i/2)) ans++;
		mp[s]++;
	}
	cout << ans;
}

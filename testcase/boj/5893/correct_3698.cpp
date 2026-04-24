#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	string s, t, ans;
	cin >> s;
	t = s + "0000";
	s = "0000" + s;
	int n = s.size();
	bool c = 0;
	for(int i=n-1; i>=0; i--) {
		bool a = s[i] == '1', b = t[i] == '1';
		int k = a+b+c;
		c = k>=2;
		ans.push_back('0'+(k&1));
	}
	if(c)
		ans.push_back('1');
	reverse(ans.begin(), ans.end());
	cout << ans;
}

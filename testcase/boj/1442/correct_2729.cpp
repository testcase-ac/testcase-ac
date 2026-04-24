#include <bits/stdc++.h>
using namespace std;
#define int long long
int dp[32][2][3];
int f(int i, int j, int t) {
	int &ret = dp[i][j][t];
	if(i < 0)
		return 0;
	if(i == 0) // error: not 1
		return t == 1 ? 1 : 0;
	if(ret != -1)
		return ret;
	if(!t) {
		ret = (f(i-1, 0, 0) + f(i-1, 1, 0) + f(i-1, j, 2));
	} else if (t == 2){
		ret = f(i-1, j, 1);
	} else if(t == 1) {
		ret = f(i-1, !j, 1) + f(i-1, !j, 2);
	} else {
		assert(false);
	}
	return ret;
}
string to_bin(int a) {
	string bin;
	while(a) {
		bin.push_back('0' + (a%2));
		a /= 2;
	}
	reverse(bin.begin(), bin.end());
	if(bin.empty()) bin = "0"; // error 2: 0
	return bin;
}
int solve(string s) {
	int ret = 0, t = 1;
	for(int i=0; i<s.size()-1; i++)
		ret += f(i, 1, 0);
	for(int i=1; i<s.size(); i++) {
		if(s[i] == '1') {
			if(!t) {
				ret += f(s.size()-1-i, 0, 1) + f(s.size()-1-i, 0, 2) + f(s.size()-1-i, 0, 0);
			} else {
				if(s[i-1] == '0') {
					if(t == 1) {
						ret += f(s.size()-1-i, 0, 2) + f(s.size()-1-i, 0, 0); 
					} else if(t == 2) {
						ret += f(s.size()-1-i, 0, 1) + f(s.size()-1-i, 0, 2) + f(s.size()-1-i, 0, 0);
					}
				} else {
					ret += f(s.size()-1-i, 0, 0);
				}
			}
		}
		if(t) { // error 3: !t should not move
			if(s[i] == s[i-1]) {
				t++;
				if(t == 3)
					t = 0;
			} else {
				if(t)
					t = 1;
			}
		}
	}
	return ret;
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	memset(dp, -1, sizeof dp);
	int a, b;
	cin >> a >> b;
	b++;
	string l = to_bin(a), r = to_bin(b);
	int ans = solve(r) - solve(l);
	cout << ans;
}

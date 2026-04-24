#include <bits/stdc++.h>
using namespace std;
int arr[100], goal[100], dp[100][10][10][10], n;
void read(int* p) {
	string s;
	cin >> s;
	for(int i=0; i<s.size(); i++)
		p[i] = s[i]-'0';
}
int mod(int i) {
	i %= 10;
	if(i < 0) i += 10;
	return i;
}
int f(int i, int x, int y, int z) {
	if(i >= n) return 0;
	int& r = dp[i][x][y][z];
	if(r != -1) return r;
	r = 1e9;
	if(mod(x+arr[i]) == mod(goal[i]))
		r = f(i+1, y, z, 0);
	for(int t=-3; t<=3; t++) {
		if(!t) continue;
		r = min(r, 1+f(i, mod(x+t), y, z));
		r = min(r, 1+f(i, mod(x+t), mod(y+t), z));
		r = min(r, 1+f(i, mod(x+t), mod(y+t), mod(z+t)));
	}
	return r;
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> n;
	read(arr);
	read(goal);
	memset(dp, -1, sizeof dp);
	cout << f(0,0,0,0);
}

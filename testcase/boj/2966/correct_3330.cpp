#include <bits/stdc++.h>
using namespace std;
int n, pt[3];
string s, name[3] = {"Adrian", "Bruno", "Goran"};
bool match(int i, vector<int> ptrn) {
	return s[i] == ('A'+ptrn[i%ptrn.size()]);
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> n >> s;
	for(int i=0; i<n; i++) {
		if(match(i, {0,1,2})) pt[0]++;
		if(match(i, {1,0,1,2})) pt[1]++;
		if(match(i, {2,2,0,0,1,1})) pt[2]++;
	}
	int mx = max({pt[0],pt[1],pt[2]});
	cout << mx << '\n';
	for(int i=0; i<3; i++) {
		if(pt[i] == mx) cout << name[i] << '\n';
	}
}

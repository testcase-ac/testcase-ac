#include <bits/stdc++.h>
using namespace std;

int pre[10], suf[10];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	string s;
	cin >> s;
	int n = s.size();
	pre[0] = s[0]-'0';
	for(int i=1; i<n; i++)
		pre[i] = pre[i-1] * (s[i]-'0');
	suf[n-1] = s[n-1]-'0';
	for(int i=n-2; i>=0; i--) 
		suf[i] = suf[i+1] * (s[i]-'0');

	for(int i=0; i<n-1; i++) {
		if(pre[i] == suf[i+1]) return !(cout << "YES");
	}
	cout << "NO";
}

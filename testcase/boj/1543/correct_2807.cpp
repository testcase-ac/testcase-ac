#include <bits/stdc++.h>
using namespace std;
void getpi(string &p, vector<int> &pi) {
	int n = p.size();
	pi.resize(n);
	int j = 0;
	for(int i=1; i<n; i++) {
		while(j && p[j] != p[i])
			j = pi[j-1];
		if(p[j] == p[i])
			j++;
		pi[i] = j;
	}
}

void KMP(string &t, string &p, vector<int> &ans) {
	vector<int> pi;
	getpi(p, pi);
	int n = t.size(), m = p.size(), j = 0;
	for(int i=0; i<n; i++) {
		while(j && p[j] != t[i])
			j = pi[j-1];
		if(p[j] == t[i])
			j++;
		if(j == m) {
			ans.push_back(i-m+1);
			j = 0;
		}
	}
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	string a, b;
	getline(cin, a);
	getline(cin, b);
	vector<int> ans;
	KMP(a, b, ans);
	cout << ans.size();
}

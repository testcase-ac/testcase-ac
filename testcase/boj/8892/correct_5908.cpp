#include <bits/stdc++.h>
using namespace std;
bool check(string& a, string& b) {
	string s = a+b;
	for(int i=0; i<s.size()/2; i++) {
		if(s[i] != s[s.size()-1-i]) return 0;
	}
	return 1;
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int T;
	cin >> T;
	while(T--) {
		int n;
		cin >> n;
		string arr[n];
		for(int i=0; i<n; i++)
			cin >> arr[i];
		for(int i=0; i<n; i++) {
			for(int j=0; j<n; j++) {
				if(i == j) continue;
				if(check(arr[i], arr[j])) {
					cout << arr[i]+arr[j] << '\n';
					goto out;
				}
			}
		}
		cout << "0\n";
		out:;
	}
}

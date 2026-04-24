#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	string s;
	cin >> s;
	int sc = 0;
	for(char c: s) {
		if(c == 'S') sc++;
	}
	cout << min(1+sc+(n-sc)/2, n);
}

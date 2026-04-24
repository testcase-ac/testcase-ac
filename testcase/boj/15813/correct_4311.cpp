#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, t = 0;
	string s;
	cin >> n >> s;
	for(char c: s)
		t += c-'A'+1;
	cout << t;
}
